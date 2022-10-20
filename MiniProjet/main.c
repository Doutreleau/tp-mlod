 
#include "raylib.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#define NULL ((void*)0)
 
struct node *new_node(char* value);
void print(struct node *root_node);
struct node* create_root_node(struct node* node, char* value);
struct node* insert_right_node(struct node* parent_node, char* child_value);
struct node* insert_left_node(struct node* parent_node, char* child_value);
struct node * create_tree();
 
typedef struct node
{
  char* value;
  struct node *left_child, *right_child;
}node ;
 
int main(void)
{
   // Initialization
   //---------------------------------------------------------
   const int screenWidth = 800;
   const int screenHeight = 350;
 
   InitWindow(screenWidth, screenHeight, "projet");
 
   node * current_node = create_tree();
   node * next_node = NULL;
 
   bool first_event = true;
   bool choose_left = false;
   bool choose_right = false;
 
   SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
   //----------------------------------------------------------
 
   // Main game loop
   while (!WindowShouldClose())    // Detect window close button or ESC key
   {
       // Update
       //-----------------------------------------------------
       if (IsKeyPressed(KEY_LEFT)) {
           first_event = false; //pb : this will be done every time we press the key, instead of only be done once. ërhaps if I change the position of if(first_event), I can get rid of this line?
           choose_left = true;
           choose_right = false;
       }
       if (IsKeyPressed(KEY_RIGHT)) {
           first_event = false;
           choose_left = false;
           choose_right = true;
       }
       if (first_event){
           ClearBackground(RAYWHITE);
           DrawText(current_node->value, 190, 200, 20, LIGHTGRAY);
       }
      
 
       else if (choose_left)
       {
           next_node = current_node->left_child;
           if (next_node !=NULL){
               ClearBackground(RAYWHITE);
               DrawText(next_node->value, 190, 200, 20, LIGHTGRAY);
               current_node = next_node;
               choose_left = false;
           }
       }
 
      
       else if (choose_right) {
           next_node = current_node->right_child;
           if (next_node !=NULL){
               ClearBackground(RAYWHITE);
               DrawText(next_node->value, 190, 200, 20, LIGHTGRAY);
               current_node = next_node;
               choose_right = false;
           }
          
       }
 
       BeginDrawing();
           DrawText("PRESS LEFT OR RIGHT ARROW", 10, GetScreenHeight() - 25, 20, LIGHTGRAY);
       EndDrawing();
   }
 
   // De-Initialization
   //---------------------------------------------------------
   CloseWindow();        // Close window and OpenGL context
   //----------------------------------------------------------
 
   return 0;
}
 
 
 
node *new_node(char* value)
{
  node *tmp = (struct node *)malloc(sizeof(struct node));
  tmp->value = value;
  tmp->left_child = tmp->right_child = NULL;
  return tmp;
}
void print(node *root_node) // displaying the nodes!
{
  if (root_node != NULL)
  {
      print(root_node->left_child);
      printf("%s \n", root_node->value);
      print(root_node->right_child);
  }
}
 
node* create_root_node(node* node, char* value) // inserting nodes!
{
  return new_node(value);
}
node* insert_right_node(node* parent_node, char* child_value) // inserting nodes!
{
  parent_node->right_child = new_node(child_value);
}
node* insert_left_node(node* parent_node, char* child_value) // inserting nodes!
{
  parent_node->left_child = new_node(child_value);
}
node * create_tree()
{
   node *root_node = NULL;
   root_node = create_root_node(root_node, "Node A, root node");
   node * node_B = insert_left_node(root_node, "Node B, left child node of A");
   node * node_C = insert_right_node(root_node, "Node C, right child node of A");   
   node * node_D = insert_left_node(node_B, "Node D, left child node of B");
   node * node_E = insert_right_node(node_B, "Node E, left child node of B");
   node * node_F = insert_left_node(node_D, "Node F, left child node of D");
   node * node_G = insert_right_node(node_D, "Node G, left child node of D");
   node * node_H = insert_left_node(node_C, "Node H, left child node of C");
   node * node_I = insert_right_node(node_C, "Node I, left child node of C");
   return root_node;
}
 
 
 

