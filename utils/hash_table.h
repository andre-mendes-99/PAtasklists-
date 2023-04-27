#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdbool.h>
#include "list.h"

#define DEFAULT_SIZE 100

typedef struct t_HashTable* HashTable;

/**
 * @brief Creates a new hash table.
 * 
 * @param size The initial size of the hash table.
 * @param hash The hash function to use.
 * @param key_equal The function to compare keys.
 * @param key_destroy The function to free keys.
 * @return HashTable The new hash table.
 */
HashTable hash_table_create(int size, int (*hash)(void*, int), bool (*key_equal)(void*, void*), void (*key_destroy)(void*));

/**
 * @brief Destroys a hash table.
 * 
 * Frees all memory allocated for the hash table, and for all keys and values of the hash table.
 * 
 * @param htable The hash table to destroy.
 * @param key_destroy The function to free keys.
 * @param value_destroy The function to free values.
 */
void hash_table_destroy(HashTable htable, void (*value_destroy)(void*));

/**
 * @brief Inserts a new key-value pair into the hash table.
 * 
 * @param htable The hash table.
 * @param key The key.
 * @param value The value.
 */
void hash_table_insert(HashTable htable, void* key, void* value);

/**
 * @brief Removes a key-value pair from the hash table.
 * 
 * @param htable The hash table.
 * @param key The key.
 * @return void* The value associated with the key.
 */
void* hash_table_remove(HashTable htable, void* key);

/**
 * @brief Returns the value associated with the key.
 * 
 * @param htable The hash table.
 * @param key The key.
 * @return void* The value associated with the key.
 */
void* hash_table_get(HashTable htable, void* key);

/**
 * @brief Updates the value associated with the key.
 * 
 * @param htable The hash table.
 * @param key The key.
 * @param value The new value.
 * @return void* The old value associated with the key.
 */
void* hash_table_update(HashTable htable, void* key, void* value);

/**
 * @brief Returns the number of elements in the hash table.
 * 
 * @param htable The hash table.
 * @return int The number of elements in the hash table.
 */
int hash_table_size(HashTable htable);

/**
 * @brief Returns true iff the hash table contains no elements.
 * 
 * @param htable The hash table.
 * @return true iff the hash table contains no elements.
 */
bool hash_table_is_empty(HashTable htable);

/**
 * @brief Returns true iff the hash table contains no elements.
 * 
 * @param htable The hash table.
 * @return true iff the hash table contains no elements.
 */
List hash_table_keys(HashTable htable);

/**
 * @brief Returns the keys of the hash table.
 * 
 * @param htable The hash table.
 * @return List The keys of the hash table.
 */
List hash_table_values(HashTable htable);

/**
 * @brief Returns the values of the hash table.
 * 
 * @param htable The hash table.
 * @return List The values of the hash table.
 */
List hash_table_entries(HashTable htable);

/**
 * @brief Returns the entries of the hash table.
 * 
 * @param htable The hash table.
 * @return List The entries of the hash table.
 */
void hash_table_rehash(HashTable htable, int new_size);

#endif