#include <stdio.h>
#include <stdlib.h>

// RecordType remains unchanged
struct RecordType
{
  int   id;
  char  name;
  int   order; 
};

// Node structure for chaining
struct Node
{
    struct RecordType data;
    struct Node *next;
};

// Fill out this structure
struct HashType
{
    struct Node **buckets;  // Array of pointers to Nodes
    int size;              // Size of the hash table
};

// Compute the hash function
int hash(int x, int tableSize)
{
    return x % tableSize;
}

int parseData(char* inputFileName, struct RecordType** ppData)
{
  FILE* inFile = fopen(inputFileName, "r");
  int dataSz = 0;
  int i, n;
  char c;
  struct RecordType *pRecord;
  *ppData = NULL;

  if (inFile)
  {
    fscanf(inFile, "%d\n", &dataSz);
    *ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
    // Implement parse data block
    if (*ppData == NULL)
    {
      printf("Cannot allocate memory\n");
      exit(-1);
    }
    for (i = 0; i < dataSz; ++i)
    {
      pRecord = *ppData + i;
      fscanf(inFile, "%d ", &n);
      pRecord->id = n;
      fscanf(inFile, "%c ", &c);
      pRecord->name = c;
      fscanf(inFile, "%d ", &n);
      pRecord->order = n;
    }

    fclose(inFile);
  }

  return dataSz;
}


void printRecords(struct RecordType pData[], int dataSz)
{
  int i;
  printf("\nRecords:\n");
  for (i = 0; i < dataSz; ++i)
  {
    printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
  }
  printf("\n\n");
}

// Initializes a hash table with the given size
struct HashType* initHashTable(int size) {
    struct HashType *ht = malloc(sizeof(struct HashType));
    ht->buckets = malloc(sizeof(struct Node*) * size);
    ht->size = size;
    for (int i = 0; i < size; i++) {
        ht->buckets[i] = NULL;
    }
    return ht;
}

// Inserts a record into the hash table
void insertRecord(struct HashType *hashTable, struct RecordType record) {
    int index = hash(record.id, hashTable->size);
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->data = record;
    newNode->next = hashTable->buckets[index];
    hashTable->buckets[index] = newNode;
}

// Displays the records in the hash table
void displayRecordsInHash(struct HashType *pHashArray) {
    struct Node *current;
    for (int i = 0; i < pHashArray->size; ++i) {
        current = pHashArray->buckets[i];
        if (current != NULL) {
            printf("index %d -> ", i);
            while (current != NULL) {
                printf("%d, %c, %d -> ", current->data.id, current->data.name, current->data.order);
                current = current->next;
            }
            printf("NULL\n");
        }
    }
}

int main(void) {
    struct RecordType *pRecords;
    int recordSz = 0;

    recordSz = parseData("input_lab_9.txt", &pRecords);
    printRecords(pRecords, recordSz);

    // Initialize and fill hash table
    struct HashType *hashTable = initHashTable(23); // Example size
    for (int i = 0; i < recordSz; ++i) {
        insertRecord(hashTable, pRecords[i]);
    }

    displayRecordsInHash(hashTable);

    // Cleanup code should be here (not provided)

    return 0;
}



