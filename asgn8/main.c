#include "io.h"
#include "trie.h"
#include "word.h"

#include <fcntl.h>
#include <getopt.h>
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

uint64_t compressed_len = 0;
uint64_t long_word = 0;
int main(int argc, char **argv) {
  bool verbose = false;
  bool compression = false;
  bool decompression = false;
  char *inputfile = NULL;
  char *outputfile = NULL;
  int c = 0;
  int input;
  int output;
  if (strcmp(argv[0], "encode") == 0) {
    compression = true;
  }
  if (strcmp(argv[0], "./encode") == 0) {
    compression = true;
  }
  if (strcmp(argv[0], "decode") == 0) {
    decompression = true;
  }
  if (strcmp(argv[0], "./decode") == 0) {
    decompression = true;
  }

  while ((c = getopt(argc, argv, "-vcdi:o:")) != -1) {
    if (c == 'v') {
      verbose = true;
    }
    if (c == 'c') {
      compression = true;
    }
    if (c == 'd') {
      decompression = true;
    }
    if (c == 'i') {
      inputfile = strdup(optarg);
    }
    if (c == 'o') {
      outputfile = strdup(optarg);
    }
  }
  if (inputfile) {
    input = open(inputfile, O_RDONLY);
  }
  if (!inputfile || input < 0) {
    input = 0;
  }
  if (inputfile) {
    free(inputfile);
  }
  if (outputfile) {
    output = open(outputfile, O_CREAT | O_RDWR | O_TRUNC, 0600);
  }
  if (!outputfile || output < 0) {
    output = 1;
  }
  if (outputfile) {
    free(outputfile);
  }
  FileHeader header;

  //I want to give credit to Eugene Chow for the psuedo code in order
  //to develop this code(inside of the if statement)
  if (compression && !decompression) {
    //  FileHeader header;
    struct stat stats;
    fstat(input, &stats);
    header.file_size = stats.st_size;
    header.protection = stats.st_mode;
    header.magic = MAGIC;
    write_header(output, &header);
    TrieNode *root = trie_create();
    TrieNode *curr_node = root;
    uint16_t next_avail_code = 256;
    uint64_t encoded_chars = 0;
    uint8_t curr_char;
    uint8_t bit_len;
    long_word += 1;
    while (encoded_chars != header.file_size) {
      curr_char = next_char(input);
      TrieNode *next_node = trie_step(curr_node, curr_char);
      if (encoded_chars == 0 || next_node) {
        curr_node = next_node;
      } else {
        bit_len = (uint8_t)log2((double)next_avail_code) + 1;
        buffer_code(output, curr_node->code, bit_len);
        curr_node->children[curr_char] = trie_node_create(next_avail_code);
        long_word += 1;
        curr_node = root->children[curr_char];
        next_avail_code += 1;
      }
      encoded_chars += 1;
      if (next_avail_code == UINT16_MAX) {
        trie_reset(root);
        curr_node = root->children[curr_char];
        next_avail_code = 256;
      }
    }
    bit_len = (uint8_t)log2((double)next_avail_code) + 1;
    buffer_code(output, curr_node->code, bit_len);
    flush_code(output);
    trie_delete(root);
  }
  //I would like to also credit Eugene for the psuedo code below
  if (decompression && !compression) {
    //does read_header
    // FileHeader header;
    read_header(input, &header);
    //creates the word table
    WordTable *table = wt_create();
    //next avail code = 256
    uint16_t next_avail_code = 256;
    bool reset = false;
    uint64_t decoded_chars = 0;
    uint8_t bit_len;
    uint16_t curr_code = 0;
    uint64_t prev_size = 4096;
    uint64_t curr_size = 4096;
    uint64_t new_size = 4096;
    uint8_t *prev_word
        = (uint8_t *)calloc(prev_size, sizeof(uint8_t)); //need to calloc
    uint8_t *curr_word
        = (uint8_t *)calloc(curr_size, sizeof(uint8_t)); //need to calloc
    uint8_t *new_word = (uint8_t *)calloc(new_size, sizeof(uint8_t)); //free
    Word *curr_entry = NULL;
    Word *prev_entry = NULL;
    Word *missing_entry;
    uint16_t prev_code = 0;
    while (decoded_chars != header.file_size) {
      bit_len = (uint8_t)log2((double)(next_avail_code + 1)) + 1;
      curr_code = next_code(input, bit_len);
      curr_entry = table->entries[curr_code];
      if (decoded_chars == 0 || reset) {
        buffer_word(output, curr_entry);
        prev_word = curr_entry->word;
        reset = false;
        decoded_chars += 1;
      } else if (curr_entry != NULL) {

        curr_word = curr_entry->word;
        prev_entry = table->entries[prev_code];
        prev_word = prev_entry->word;
        if ((prev_entry->word_len + 1) > new_size) {
          new_size = new_size * 2;
          new_word = (uint8_t *)realloc(new_word, new_size);
        }
        for (uint64_t i = 0; i < prev_entry->word_len; i++) {
          new_word[i] = prev_word[i];
        }
        new_word[prev_entry->word_len] = curr_word[0];

        table->entries[next_avail_code]
            = word_create(new_word, (prev_entry->word_len + 1));
        next_avail_code += 1;
        buffer_word(output, curr_entry);
        decoded_chars += curr_entry->word_len;
      } else {
        prev_entry = table->entries[prev_code];
        prev_word = prev_entry->word;
        if ((prev_entry->word_len + 1) > curr_size) {
          curr_size = curr_size * 2;
          curr_word = (uint8_t *)realloc(curr_word, curr_size);
        }
        for (uint64_t i = 0; i < prev_entry->word_len; i++) {
          curr_word[i] = prev_word[i];
        }
        curr_word[prev_entry->word_len] = prev_word[0]; //curr_word
        missing_entry = word_create(curr_word, prev_entry->word_len + 1);
        table->entries[next_avail_code] = missing_entry;
        next_avail_code += 1;
        buffer_word(output, missing_entry);
        decoded_chars += missing_entry->word_len;
      }
      prev_code = curr_code; //
      if (next_avail_code == UINT16_MAX - 1) {
        wt_reset(table);
        next_avail_code = 256;
        reset = true;
      }
    }
    flush_word(output);
    free(prev_word);
    free(curr_word);
    free(new_word);
    //word_delete(curr_entry);
    //word_delete(prev_entry);
    //word_delete(missing_entry);
    wt_delete(table);
  }
  if ((compression && decompression) || (!compression && !decompression)) {
    printf(
        "you must chose compression or decompression not both or niether.\n");
  }
  if (verbose) {
    printf("\nOrigial file size: %" PRIu64 "\n", header.file_size);
    printf("\nCompressed file size: %" PRIu64 "\n", compressed_len);
    //The compresion ratio logic was provided by eugene chow
    printf("\nCompression ratio: %2.4f%% \n",
        (100 * (1 - ((double)compressed_len / (double)header.file_size))));
    printf("\nLongest word length: %" PRIu64 "\n", long_word);
  }
  if (input == 0) {
    close(input);
  }
  if (output == 1) {
    close(output);
  }
  return 0;
}
