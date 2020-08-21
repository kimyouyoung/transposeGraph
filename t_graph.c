#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTEICSES 20
int n = 0;
typedef struct GraphNode{
    int vertex;
    struct GraphNode *next;
}GraphNode;

typedef struct{
    int n;
    GraphNode *adj_list[MAX_VERTEICSES];
}Graph;

void adjacencyList(Graph graph, char alpha[]){

    printf("\n==== Array of adjacency list of above graph ====\n");

    for(int i = 0; i < graph.n; i++){
        printf("|-----| \n");
        GraphNode *temp = graph.adj_list[i];
        printf("|  %c  | ", alpha[i]);
        temp = temp->next;
        while(1){
            if(temp == NULL)
                break;
            
            printf("--> %c ", alpha[temp->vertex]);
            
            temp = temp->next;
        }
        printf("\n");
    }
    printf("|_____|\n\n");
}

void adjacencyListTranspose(Graph graph, char alpha[]){

    Graph trans_graph;
    trans_graph.n = graph.n;

    for(int i = 0; i < trans_graph.n; i++){
        GraphNode *node = (GraphNode*)malloc(sizeof(GraphNode));
        node->vertex = i;
        node->next = NULL;
        trans_graph.adj_list[i] = node;
    }

    
    for(int i = 0; i < graph.n; i++){
        GraphNode *temp = graph.adj_list[i];
        GraphNode *pre = temp;
        temp = temp->next;
        while(1){
            if(temp == NULL)
                break;

            GraphNode *node = trans_graph.adj_list[temp->vertex];
            while(1){
                if(node->next == NULL){
                    GraphNode *trans_node = (GraphNode*)malloc(sizeof(GraphNode));
                    trans_node->vertex = pre->vertex;
                    trans_node->next = NULL;
                    node->next = trans_node;
                    break;
                }
                node = node->next;
            }
            temp = temp->next;
        }
    }

    printf("\n===== Array of adjacency list of transpose graph ====\n");

    for(int i = 0; i < trans_graph.n; i++){
        printf("|-----| \n");
        GraphNode *temp = trans_graph.adj_list[i];
        printf("|  %c  | ", alpha[i]);
        temp = temp->next;
        while(1){
            if(temp == NULL)
                break;
            
            printf("--> %c ", alpha[temp->vertex]);
            
            temp = temp->next;
        }
        printf("\n");
    }
    printf("|_____|\n\n");
}

void resize(int *size, char **str){

    int newsize = (*size) * 2;
    char *temp = malloc(sizeof(char) * newsize);

    for(int i = 0; i < newsize; i++)
        temp[i] = (*str)[i];
    
    free(*str);
    *str = temp;
    *size = newsize;

}

int main(){

    FILE *fp = fopen("hw6_data.txt", "r");

    // if the file does not exist or there is an error in the file, exit the program
    if(fp == NULL){
        printf("Can't Open!:(\n");
        exit(1);
    }
    int size = 128;
    int num = 0, s = 0;
    char buffer[size];
    int repeat = 1;

    // count number of node
    while(repeat){
        fgets(buffer, sizeof(buffer), fp);

        for(int i = 0; i < strlen(buffer); i++){
            if((buffer[i] >= 'A' && buffer[i] <= 'Z') || (buffer[i] >= 'a' && buffer[i] <= 'z')){
                s++;
                repeat = 0;
            }
        }
    }

    Graph graph;
    // insert vertices
    graph.n = s;
    // Assume number of nodes in your graph is less than or equal to 20.
    if(graph.n > 20){
            printf("Maxinum number of node = 20, try again!:)\n");
            exit(1);
    }

    char alpha[s];
    int al = 0;
    char *save = malloc(sizeof(char) * size);
    int index = 0, m = 0;
    repeat = 0;

    // Read the contents of the file line by line.
    while(!feof(fp)){
        fgets(buffer, sizeof(buffer), fp);

        // if array size is insufficient, double.
        if(size == num)
            resize(&size, &save);

        for(int i = 0; i < strlen(buffer); i++){
            if(buffer[i] == 48 || buffer[i] == 49){
                if(buffer[i] == 48)
                    m++;
                else if(buffer[i] == 49){
                    m++;
                    GraphNode *temp = graph.adj_list[index];
                    while(1){
                        if(temp->next == NULL){
                            GraphNode *node = (GraphNode*)malloc(sizeof(GraphNode));
                            node->vertex = m-1;
                            node->next = NULL;
                            temp->next = node;
                            break;
                        }

                        temp = temp->next;
                    }
                    
                }

                repeat = 1;
            }
            // save alphabet and make node for adj_list
            else if((buffer[i] >= 'A' && buffer[i] <= 'Z') || (buffer[i] >= 'a' && buffer[i] <= 'z')){
                GraphNode *node = (GraphNode*)malloc(sizeof(GraphNode));
                node->vertex = index;
                node->next = NULL;
                graph.adj_list[index] = node;
                alpha[index] = buffer[i];
            }
        }

        if(repeat){
            repeat = 0;
            index++;
            m = 0;
        }
    }

    adjacencyList(graph, alpha);
    adjacencyListTranspose(graph, alpha);

    fclose(fp);

    return 0;
}