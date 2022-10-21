#include "raylib.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#define NULL ((void*)0)
 
typedef struct textEvent{
   char *text, *option1, *option2, *option3, *option4;
} textEvent;
typedef struct node
{
 struct textEvent * textAndOptions;
 struct node *first_child, *second_child, *third_child, *fourth_child;
}node ;
 
 
void displayOptions(node *node);
void displayOption(Font font, char* option, int height);
textEvent *new_textEvent(char* text, char* option1, char* option2, char* option3, char* option4);
struct node *new_node(textEvent* textAndOptions);
void print(struct node *root_node);
node* create_root_node(textEvent* textAndOptions);
struct node* insert_first_child(struct node* parent_node, textEvent* child_value);
struct node* insert_second_child(struct node* parent_node, textEvent* child_value);
struct node* insert_third_child(struct node* parent_node, textEvent* child_value);
struct node* insert_fourth_child(struct node* parent_node, textEvent* child_value);
struct node * create_tree();
static void DrawTextBoxed(Font font, const char *text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint);
static void DrawTextBoxedSelectable(Font font, const char *text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint, int selectStart, int selectLength, Color selectTint, Color selectBackTint);
 
const int screenWidth = 800;
const int screenHeight = 350;
//used to make sure the text stays in the screen
Rectangle container = { 25.0f, 25.0f, screenWidth , screenHeight  };
bool wordWrap = true;
 
int main(void)
{
  // Initialization
  //---------------------------------------------------------
 
  InitWindow(screenWidth, screenHeight, "projet");
  node * current_node = create_tree();
  node * next_node = NULL;
  
  bool first_event = true;
 
  Font font = GetFontDefault();
  SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
  //----------------------------------------------------------
  // Main game loop
  while (!WindowShouldClose())    // Detect window close button or ESC key
  {
      // Update
 
     
 
      if (IsKeyPressed(KEY_LEFT)) {
         
          first_event = false; //pb : this will be done every time we press the key, instead of only be done once. ërhaps if I change the position of if(first_event), I can get rid of this line?
          next_node = current_node->first_child;
          if (next_node !=NULL){
              ClearBackground(RAYWHITE);
              DrawTextBoxed(font, next_node->textAndOptions->text, (Rectangle){ container.x + 4, container.y + 50, container.width - 4, container.height - 50 }, 20.0f, 2.0f, wordWrap, GRAY);
              displayOptions(next_node);
              current_node = next_node;
              if(next_node->first_child == NULL && next_node->second_child==NULL && next_node->third_child == NULL && next_node->fourth_child==NULL){
                  ClearBackground(RAYWHITE);
                  DrawTextBoxed(font, "end of the game", (Rectangle){ container.x + 4, container.y + 200, container.width - 4, container.height - 200 }, 20.0f, 2.0f, wordWrap, GRAY);
              }
          }
          else{
              ClearBackground(RAYWHITE);
              DrawTextBoxed(font, "end of the game", (Rectangle){ container.x + 4, container.y + 200, container.width - 4, container.height - 200 }, 20.0f, 2.0f, wordWrap, GRAY);
          }
      }
      else if (IsKeyPressed(KEY_RIGHT)) {
          first_event = false; //pb : this will be done every time we press the key, instead of only be done once. ërhaps if I change the position of if(first_event), I can get rid of this line?
          next_node = current_node->second_child;
          if (next_node !=NULL){
              ClearBackground(RAYWHITE);
              DrawTextBoxed(font, next_node->textAndOptions->text, (Rectangle){ container.x + 4, container.y + 50, container.width - 4, container.height - 50 }, 20.0f, 2.0f, wordWrap, GRAY);
              displayOptions(next_node);
             
              current_node = next_node;
              if(next_node->first_child == NULL && next_node->second_child==NULL && next_node->third_child == NULL && next_node->fourth_child==NULL){
                  ClearBackground(RAYWHITE);
                  DrawTextBoxed(font, "end of the game", (Rectangle){ container.x + 4, container.y + 200, container.width - 4, container.height - 200 }, 20.0f, 2.0f, wordWrap, GRAY);
              }
          }
          else{
              ClearBackground(RAYWHITE);
              DrawTextBoxed(font, "end of the game", (Rectangle){ container.x + 4, container.y + 200, container.width - 4, container.height - 200 }, 20.0f, 2.0f, wordWrap, GRAY);
          }
     
      }
      else if (IsKeyPressed(KEY_UP)) {
          first_event = false; //pb : this will be done every time we press the key, instead of only be done once. ërhaps if I change the position of if(first_event), I can get rid of this line?
          next_node = current_node->third_child;
          if (next_node !=NULL){
              ClearBackground(RAYWHITE);
              DrawTextBoxed(font, next_node->textAndOptions->text, (Rectangle){ container.x + 4, container.y + 50, container.width - 4, container.height - 50 }, 20.0f, 2.0f, wordWrap, GRAY);
              displayOptions(next_node);
              current_node = next_node;
              if(next_node->first_child == NULL && next_node->second_child==NULL && next_node->third_child == NULL && next_node->fourth_child==NULL){
                  ClearBackground(RAYWHITE);
                  DrawTextBoxed(font, "end of the game", (Rectangle){ container.x + 4, container.y + 200, container.width - 4, container.height - 200 }, 20.0f, 2.0f, wordWrap, GRAY);
              }
          }
          else{
              ClearBackground(RAYWHITE);
              DrawTextBoxed(font, "end of the game", (Rectangle){ container.x + 4, container.y + 200, container.width - 4, container.height - 200 }, 20.0f, 2.0f, wordWrap, GRAY);
          }
     
      }
      else if (IsKeyPressed(KEY_DOWN)) {
          first_event = false; //pb : this will be done every time we press the key, instead of only be done once. ërhaps if I change the position of if(first_event), I can get rid of this line?
          next_node = current_node->fourth_child;
          if (next_node !=NULL){
              ClearBackground(RAYWHITE);
              DrawTextBoxed(font, next_node->textAndOptions->text, (Rectangle){ container.x + 4, container.y + 50, container.width - 4, container.height - 50 }, 20.0f, 2.0f, wordWrap, GRAY);
              displayOptions(next_node);
              current_node = next_node;
              if(next_node->first_child == NULL && next_node->second_child==NULL && next_node->third_child == NULL && next_node->fourth_child==NULL){
                  ClearBackground(RAYWHITE);
                  DrawTextBoxed(font, "end of the game", (Rectangle){ container.x + 4, container.y + 200, container.width - 4, container.height - 200 }, 20.0f, 2.0f, wordWrap, GRAY);
              }
          }
          else{
              ClearBackground(RAYWHITE);
              DrawTextBoxed(font, "end of the game", (Rectangle){ container.x + 4, container.y + 200, container.width - 4, container.height - 200 }, 20.0f, 2.0f, wordWrap, GRAY);
          }
     
      }
      else if (first_event){
          ClearBackground(RAYWHITE);
          DrawTextBoxed(font, current_node->textAndOptions->text, (Rectangle){ container.x + 4, container.y + 50, container.width - 4, container.height - 50 }, 20.0f, 2.0f, wordWrap, GRAY); 
          displayOptions(current_node);
 
      }
     
   
      BeginDrawing();
          DrawText("Press an arrow", 10, GetScreenHeight() - 25, 20, LIGHTGRAY);
      EndDrawing();
  }
  // De-Initialization
  //---------------------------------------------------------
  CloseWindow();        // Close window and OpenGL context
  //----------------------------------------------------------
  return 0;
}
void displayOptions(node *node){
   Font font = GetFontDefault();
   displayOption(font, node->textAndOptions->option1, 100);
   displayOption(font, node->textAndOptions->option2, 150);
   displayOption(font, node->textAndOptions->option3, 200);
   displayOption(font, node->textAndOptions->option4, 250);
 
}
 
void displayOption(Font font, char* option, int height){
   if (option !=NULL){
       DrawTextBoxed(font, option, (Rectangle){ container.x + 4, container.y + height, container.width - 4, container.height - height }, 20.0f, 2.0f, wordWrap, GRAY);
   }
 
}
 
textEvent *new_textEvent(char* text, char* option1, char* option2, char* option3, char* option4){
   textEvent *tmp = (struct textEvent *)malloc(sizeof(struct textEvent));
   tmp -> text = text;     
   tmp -> option1 = option1;    
   tmp -> option2 = option2;       
   tmp -> option3 = option3;    
   tmp -> option4 = option4;
  
   return tmp;
}
 
node *new_node(textEvent* textAndOptions)
{
 node *tmp = (struct node *)malloc(sizeof(struct node));
 tmp->textAndOptions = textAndOptions;
 tmp->first_child = tmp->second_child = tmp->third_child = tmp->fourth_child = NULL;
 return tmp;
}
node* create_root_node( textEvent* textAndOptions) // inserting nodes!
{
 return new_node(textAndOptions);
}
node* insert_first_child(node* parent_node, textEvent* child_value) // inserting nodes!
{
 parent_node->first_child = new_node(child_value);
}
node* insert_second_child(node* parent_node, textEvent* child_value) // inserting nodes!
{
 parent_node->second_child = new_node(child_value);
}
node* insert_third_child(node* parent_node, textEvent* child_value) // inserting nodes!
{
 parent_node->third_child = new_node(child_value);
}
node* insert_fourth_child(node* parent_node, textEvent* child_value) // inserting nodes!
{
 parent_node->fourth_child = new_node(child_value);
}
node * create_tree()
{
  node *root_node = create_root_node(new_textEvent("Node A, root node","opt1","op2","op3","op4"));
  node * node_B = insert_first_child(root_node, new_textEvent("Node B, first child node of A", "B opt1", "B opt2", "B opt3", "B opt4"));
  node * node_C = insert_second_child(root_node, new_textEvent("Node C, second child node of A","C opt1", NULL, NULL, NULL)); 
  node * node_D = insert_first_child(node_B, new_textEvent("Node D, first child node of B","D opt1", NULL, NULL, NULL));
  node * node_E = insert_second_child(node_B, new_textEvent("Node E, second child node of B",NULL, NULL, NULL, NULL));
  node * node_F = insert_first_child(node_D, new_textEvent("Node F, first child node of D",NULL, NULL, NULL, NULL));
  node * node_G = insert_second_child(node_D, new_textEvent("Node G, second child node of D",NULL, NULL, NULL, NULL));
  node * node_H = insert_first_child(node_C, new_textEvent("Node H, first child node of C",NULL, NULL, NULL, NULL));
  node * node_I = insert_second_child(node_C, new_textEvent("Node I, second child node of C",NULL, NULL, NULL, NULL));
  node * node_J = insert_third_child(root_node, new_textEvent("Node J, 3rd child node of A",NULL, NULL, NULL, NULL));
  node * node_K = insert_fourth_child(root_node, new_textEvent("Node K, 4th child node of A",NULL, NULL, NULL, NULL));
  node * node_L = insert_first_child(node_J, new_textEvent("Node L, 1th child node of J",NULL, NULL, NULL, NULL));
 
  return root_node;
}
 
// The next two functions were taken from the raylib example entitled "text_rectangle_bounds", by SzieberthAdam.
// It can be found here : https://github.com/raysan5/raylib/blob/master/examples/text/text_rectangle_bounds.c
// It is used to keeo the text inside the screen.
// Draw text using font inside rectangle limits
static void DrawTextBoxed(Font font, const char *text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint)
{
  DrawTextBoxedSelectable(font, text, rec, fontSize, spacing, wordWrap, tint, 0, 0, WHITE, WHITE);
}
// Draw text using font inside rectangle limits with support for text selection
static void DrawTextBoxedSelectable(Font font, const char *text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint, int selectStart, int selectLength, Color selectTint, Color selectBackTint)
{
  int length = TextLength(text);  // Total length in bytes of the text, scanned by codepoints in loop
  float textOffsetY = 0;          // Offset between lines (on line break '\n')
  float textOffsetX = 0.0f;       // Offset X to next character to draw
  float scaleFactor = fontSize/(float)font.baseSize;     // Character rectangle scaling factor
  // Word/character wrapping mechanism variables
  enum { MEASURE_STATE = 0, DRAW_STATE = 1 };
  int state = wordWrap? MEASURE_STATE : DRAW_STATE;
  int startLine = -1;         // Index where to begin drawing (where a line begins)
  int endLine = -1;           // Index where to stop drawing (where a line ends)
  int lastk = -1;             // Holds last value of the character position
  for (int i = 0, k = 0; i < length; i++, k++)
  {
      // Get next codepoint from byte string and glyph index in font
      int codepointByteCount = 0;
      int codepoint = GetCodepoint(&text[i], &codepointByteCount);
      int index = GetGlyphIndex(font, codepoint);
      // NOTE: Normally we exit the decoding sequence as soon as a bad byte is found (and return 0x3f)
      // but we need to draw all of the bad bytes using the '?' symbol moving one byte
      if (codepoint == 0x3f) codepointByteCount = 1;
      i += (codepointByteCount - 1);
      float glyphWidth = 0;
      if (codepoint != '\n')
      {
          glyphWidth = (font.glyphs[index].advanceX == 0) ? font.recs[index].width*scaleFactor : font.glyphs[index].advanceX*scaleFactor;
          if (i + 1 < length) glyphWidth = glyphWidth + spacing;
      }
      // NOTE: When wordWrap is ON we first measure how much of the text we can draw before going outside of the rec container
      // We store this info in startLine and endLine, then we change states, draw the text between those two variables
      // and change states again and again recursively until the end of the text (or until we get outside of the container).
      // When wordWrap is OFF we don't need the measure state so we go to the drawing state immediately
      // and begin drawing on the next line before we can get outside the container.
      if (state == MEASURE_STATE)
      {
          // TODO: There are multiple types of spaces in UNICODE, maybe it's a good idea to add support for more
          // Ref: http://jkorpela.fi/chars/spaces.html
          if ((codepoint == ' ') || (codepoint == '\t') || (codepoint == '\n')) endLine = i;
          if ((textOffsetX + glyphWidth) > rec.width)
          {
              endLine = (endLine < 1)? i : endLine;
              if (i == endLine) endLine -= codepointByteCount;
              if ((startLine + codepointByteCount) == endLine) endLine = (i - codepointByteCount);
              state = !state;
          }
          else if ((i + 1) == length)
          {
              endLine = i;
              state = !state;
          }
          else if (codepoint == '\n') state = !state;
          if (state == DRAW_STATE)
          {
              textOffsetX = 0;
              i = startLine;
              glyphWidth = 0;
              // Save character position when we switch states
              int tmp = lastk;
              lastk = k - 1;
              k = tmp;
          }
      }
      else
      {
          if (codepoint == '\n')
          {
              if (!wordWrap)
              {
                  textOffsetY += (font.baseSize + font.baseSize/2)*scaleFactor;
                  textOffsetX = 0;
              }
          }
          else
          {
              if (!wordWrap && ((textOffsetX + glyphWidth) > rec.width))
              {
                  textOffsetY += (font.baseSize + font.baseSize/2)*scaleFactor;
                  textOffsetX = 0;
              }
              // When text overflows rectangle height limit, just stop drawing
              if ((textOffsetY + font.baseSize*scaleFactor) > rec.height) break;
              // Draw selection background
              bool isGlyphSelected = false;
              if ((selectStart >= 0) && (k >= selectStart) && (k < (selectStart + selectLength)))
              {
                  DrawRectangleRec((Rectangle){ rec.x + textOffsetX - 1, rec.y + textOffsetY, glyphWidth, (float)font.baseSize*scaleFactor }, selectBackTint);
                  isGlyphSelected = true;
              }
              // Draw current character glyph
              if ((codepoint != ' ') && (codepoint != '\t'))
              {
                  DrawTextCodepoint(font, codepoint, (Vector2){ rec.x + textOffsetX, rec.y + textOffsetY }, fontSize, isGlyphSelected? selectTint : tint);
              }
          }
          if (wordWrap && (i == endLine))
          {
              textOffsetY += (font.baseSize + font.baseSize/2)*scaleFactor;
              textOffsetX = 0;
              startLine = endLine;
              endLine = -1;
              glyphWidth = 0;
              selectStart += lastk - k;
              k = lastk;
              state = !state;
          }
      }
      if ((textOffsetX != 0) || (codepoint != ' ')) textOffsetX += glyphWidth;  // avoid leading spaces
  }
}
 
 
 

