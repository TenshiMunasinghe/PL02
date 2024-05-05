#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define HASH_SIZE 33
#define MAX_DATA_SIZE 256
#define MAX_BLOCK_LENGTH 100
#define MAX_NONCE 1000000

int GLOBAL_NONCE_ARRAY[MAX_BLOCK_LENGTH];

typedef struct block
{
    int index;
    time_t timestamp;
    char data[MAX_DATA_SIZE];
    char previousHash[HASH_SIZE];
    char hash[HASH_SIZE];
    int nonce;
} Block;

typedef struct BlockNode
{
    Block block;
    struct BlockNode *next;
} BlockNode;

// function prototypes (forward declaration)
void simpleHash(char *input, char output[HASH_SIZE]);
Block createGenesisBlock();
Block createBlock(Block previousBlock, char *data);
BlockNode *createGenesisNode();
BlockNode *addBlock(BlockNode *lastNode, char *data);
int isBlockValid(Block newBlock, Block previousBlock);
int isChainValid(BlockNode *head);
bool isNonceUsed(int element);

bool isNonceUsed(int element)
{
    for (int i = 0; i < MAX_BLOCK_LENGTH; i++)
    {
        if (GLOBAL_NONCE_ARRAY[i] == element)
            return true;
    }
    return false;
}

void hashBlock(Block *block)
{
    int nonce = -1;
    char temp[1024] = {0}; // init to zero
    char leadingChars[3];
    do
    {
        nonce++;
        block->nonce = nonce;
        if (nonce > MAX_NONCE)
        {
            printf("Max nonce exceeded.\n");
            break;
        }
        sprintf(temp,
                "%d%s%lld%s%d", block->index, block->previousHash, (long long)block->timestamp, block->data, nonce);
        simpleHash(temp, block->hash);
        strncpy(leadingChars, block->hash, 3); // Read first 3 characters.
    } while (strcmp("000", leadingChars) != 0 || isNonceUsed(nonce) == true);
};

void simpleHash(char *input, char output[HASH_SIZE]) // WARNING: This algorithm is too poor to produce a hash with leading zeroes.
{
    for (int i = 0; i < HASH_SIZE - 1; i++)
    {
        output[i] = 0;
    }
    for (int i = 0; input[i] != '\0'; i++)
    {
        output[i % (HASH_SIZE - 1)] ^= input[i];
    }

    output[HASH_SIZE - 1] = '\0'; // null-terminate the hash
}

Block createGenesisBlock()
{
    Block genesis = {0}; // init all fields to zero
    genesis.index = 0;
    strcpy(genesis.previousHash, "0");
    genesis.timestamp = time(NULL);
    strcpy(genesis.data, "Genesis Block");
    hashBlock(&genesis);
    return genesis;
}

Block createBlock(Block previousBlock, char *data)
{
    Block newBlock = {0};
    newBlock.index = previousBlock.index + 1;
    strcpy(newBlock.previousHash, previousBlock.hash);
    newBlock.timestamp = time(NULL);
    strcpy(newBlock.data, data);
    hashBlock(&newBlock);

    return newBlock;
}

BlockNode *createGenesisNode()
{
    BlockNode *genesisNode = (BlockNode *)malloc(sizeof(BlockNode));
    if (genesisNode == NULL)
    {
        fprintf(stderr, "Out of memory!\n");
        exit(1);
    }
    genesisNode->block = createGenesisBlock();
    genesisNode->next = NULL;
    return genesisNode;
}

BlockNode *addBlock(BlockNode *lastNode, char *data)
{
    Block newBlock = createBlock(lastNode->block, data);
    if (isBlockValid(newBlock, lastNode->block))
    {
        BlockNode *newNode = (BlockNode *)malloc(sizeof(BlockNode));
        if (newNode == NULL)
        {
            fprintf(stderr, "Out of memory!\n");
            exit(1);
        }
        newNode->block = newBlock;
        newNode->next = NULL;
        lastNode->next = newNode;
        return newNode;
    }
    else
    {
        fprintf(stderr, "Invalid block!\n");
        return NULL;
    }
}

int isBlockValid(Block newBlock, Block previousBlock)
{
    if (newBlock.index != previousBlock.index + 1)
    {
        return 0;
    }
    if (strcmp(newBlock.previousHash, previousBlock.hash) != 0)
    {
        return 0;
    }
    // char recalculatedHash[HASH_SIZE] = {0};

    // if (strcmp(recalculatedHash, newBlock.hash) != 0)
    // {
    //     return 0;
    // }
    return 1;
}

int isChainValid(BlockNode *head)
{
    BlockNode *current = head;
    while (current && current->next)
    {
        if (!isBlockValid(current->next->block, current->block))
        {
            return 0;
        }
        current = current->next;
    }
    return 1;
}

int main()
{
    BlockNode *blockchain = createGenesisNode();
    printf("Genesis Block has been created with hash: %s\n\n", blockchain->block.hash);

    BlockNode *lastNode = blockchain;
    char data[MAX_DATA_SIZE];
    int blockchainLength = 1; // genesis block = 1

    while (1)
    {
        printf("Enter new-block data ('exit' to stop): ");
        fgets(data, sizeof(data), stdin);
        data[strcspn(data, "\n")] = 0; // Remove newline character

        // condition --> exit
        if (strcmp(data, "exit") == 0)
        {
            break;
        }

        // Info --> new block
        lastNode = addBlock(lastNode, data);
        if (lastNode != NULL)
        {
            blockchainLength++;
            printf("\nBlock added with new hash: %s\n", lastNode->block.hash);
            printf("\nNew block index: %d\n", lastNode->block.index);
            printf("New block prev hash: %s\n", lastNode->block.previousHash);
            printf("New block data: %s\n", lastNode->block.data);
            printf("\nCurrent blockchain length: %d\n\n", blockchainLength);
        }
        else
        {
            fprintf(stderr, "Failed to add new block.\n");
        }
    }

    if (isChainValid(blockchain))
    {
        printf("The blockchain is valid.\n");
    }
    else
    {
        printf("The blockchain is invalid!\n");
    }

    // Free --> allocated memory
    BlockNode *current = blockchain;
    while (current)
    {
        BlockNode *toFree = current;
        current = current->next;
        free(toFree);
    }

    printf("Blockchain program exited.\n");
    return 0;
}