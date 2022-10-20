 
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
   const int screenHeight = 450;
 
   InitWindow(screenWidth, screenHeight, "projet");
 
   node * current_node = create_tree();
   char * val = current_node->value;
   bool pause = false;
 
   SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
   //----------------------------------------------------------
 
   // Main game loop
   while (!WindowShouldClose())    // Detect window close button or ESC key
   {
       // Update
       //-----------------------------------------------------
       if (IsKeyPressed(KEY_SPACE)) pause = !pause;
 
       if (!pause)
       {
           DrawText(val, 190, 200, 20, LIGHTGRAY);
 
       }
       else {
           DrawText("Second window", 190, 200, 20, LIGHTGRAY);
       }
       //-----------------------------------------------------
 
       // Draw
       //-----------------------------------------------------
       BeginDrawing();
 
           ClearBackground(RAYWHITE);
           DrawText("PRESS SPACE TO CHANGE WINDOW", 10, GetScreenHeight() - 25, 20, LIGHTGRAY);
 
 
       EndDrawing();
       //-----------------------------------------------------
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
  
   node * node_D = insert_left_node(node_B, "Node D, left child node of D");
   return root_node;
}
 
 
 

