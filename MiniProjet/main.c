 
#include "raylib.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <time.h>
#define NULL ((void*)0)
#define customColor_lightBrown  (Color){ 211, 176, 148, 255 }
#define customColor_darkBrown  (Color){ 189, 152, 123, 255 }

//the text shown on the screen is made of 5 different texts : the text of the event, and the text of the different options. Those two types of texts were split in a struct in order to make it easier to display.
typedef struct textEvent{
    char *text, *option1, *option2, *option3, *option4;
} textEvent;

typedef struct node
{
  struct textEvent * textAndOptions;
  int proba;
  struct node *first_child[3], *second_child[3], *third_child[3], *fourth_child[3]; //a node has up to 4 options, and each option can have up to 3 children, the elected child will be chosen randomly
}node ;


//defining all the functions
void drawBackground(Font font, Texture background_texture);
void displayOptions(node *node);
void displayOption(Font font, char* option, int height);
textEvent *new_textEvent(char* text, char* option1, char* option2, char* option3, char* option4);
node *new_node_with_proba(textEvent* textAndOptions, int proba);
void print(struct node *root_node);
node* create_root_node(textEvent* textAndOptions);
node* insert_first_child(node* parent_node, textEvent* child_value, int proba, int position);
struct node* insert_second_child(struct node* parent_node, textEvent* child_value, int proba, int position);
struct node* insert_third_child(struct node* parent_node, textEvent* child_value, int proba, int position);
struct node* insert_fourth_child(struct node* parent_node, textEvent* child_value, int proba, int position);
struct node * create_tree(node*root_node);
void destroyTree(node * root_node);

void initialiseNode(node *node);
 
static void DrawTextBoxed(Font font, const char *text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint);
static void DrawTextBoxedSelectable(Font font, const char *text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint, int selectStart, int selectLength, Color selectTint, Color selectBackTint);
 

const int screenWidth = 711;
const int screenHeight = 400;

//used to make sure the text stays in the screen
Rectangle container = { 25.0f, 25.0f, screenWidth , screenHeight  };
bool wordWrap = true;

int main(void)
{
   // Initialization
   //---------------------------------------------------------
   
 
   InitWindow(screenWidth, screenHeight, "projet");

   srand(time(NULL)); //used to generate random nmbers


   //generate the welcoming image

    Image welcome_page_image = LoadImage("resources/welcome.png");     // Loaded in CPU memory (RAM)
    ImageResize(&welcome_page_image, 711, 400);
    Texture2D welcome_page_texture = LoadTextureFromImage(welcome_page_image);          // Image converted to texture, GPU memory (VRAM)
    UnloadImage(welcome_page_image);   // Once image has been converted to texture and uploaded to VRAM, it can be unloaded from RAM

    Image background_image = LoadImage("resources/background.png");     // Loaded in CPU memory (RAM)
    ImageResize(&background_image, 711, 400);
    Texture2D background_texture = LoadTextureFromImage(background_image);          // Image converted to texture, GPU memory (VRAM)
    UnloadImage(background_image);   // Once image has been converted to texture and uploaded to VRAM, it can be unloaded from RAM

    // generate the tree
    node *root_node = create_root_node(new_textEvent("Node A, root node","opt1","op2","op3","op4")); // we need to generate the root node separately in order to easily retrieve it when we free the allocated memory
   node * current_node = create_tree(root_node);
   node * next_node = NULL;

   bool welcome_page = true; //boolean to know whether to display the welcoming page or not.
   bool first_event = false; //boolean to know whether to display the first event or not.
   bool end_game = false; //boolean to know whether to display the text of the end of the game.
   
   Font font = GetFontDefault();
 
   SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
   //----------------------------------------------------------
   // Main game loop
   while (!WindowShouldClose())    // Detect window close button or ESC key
   {
       // Update


       if (IsKeyPressed(KEY_LEFT)&(!welcome_page)) { //first child
           
           first_event = false; 
           
           if(current_node->first_child[0] == NULL){ //if the user pressed the key, but that there is no option for that key (ie the user made a mistake)
               DrawTextBoxed(font, "this is not a valid option", (Rectangle){ container.x + 40, container.y + 270, container.width - 40, container.height - 270 }, 20.0f, 2.0f, wordWrap, customColor_darkBrown);
            }
            else{
                int random_number = rand()%100;      // Returns a pseudo-random integer between 0 and 99.
                //we determine the next event, based on the random number
                if (random_number < (current_node->first_child[0]->proba)){ 
                    next_node = current_node->first_child[0];            
                }
                else if((random_number) < ((current_node->first_child[1]->proba)+(current_node->first_child[0]->proba))){
                    next_node = current_node->first_child[1];
                }
                else{
                    next_node = current_node->first_child[2];
                }
                //display the background, the text and the options
                ClearBackground(RAYWHITE);
                drawBackground(font,background_texture);
                DrawTextBoxed(font, next_node->textAndOptions->text, (Rectangle){ container.x + 40, container.y + 50, container.width - 40, container.height - 50 }, 20.0f, 2.0f, wordWrap, customColor_darkBrown);
                displayOptions(next_node);

                current_node = next_node;
                if(next_node->first_child[0] == NULL && next_node->first_child[1] == NULL && next_node->first_child[2] == NULL && next_node->second_child[0] == NULL && next_node->second_child[1] == NULL && next_node->second_child[2] == NULL && next_node->third_child[0] == NULL && next_node->third_child[1] == NULL && next_node->third_child[2] == NULL && next_node->fourth_child[0] == NULL && next_node->fourth_child[1] == NULL && next_node->fourth_child[2] == NULL ){
                    end_game = true;//if the next node has no children, it is the end of the game
                }
            }   
       
       }
 
       else if (IsKeyPressed(KEY_RIGHT)&(!welcome_page)) {
           first_event = false; 
           int random_number = rand()%100;      // Returns a pseudo-random integer between 0 and 99.
           
           if(current_node->second_child[0] == NULL){
               DrawTextBoxed(font, "this is not a valid option", (Rectangle){ container.x + 40, container.y + 270, container.width - 40, container.height - 270 }, 20.0f, 2.0f, wordWrap, customColor_darkBrown);
            }
            else{
                if (random_number < (current_node->second_child[0]->proba)){ 
                    next_node = current_node->second_child[0];            
                }
                else if((random_number) < ((current_node->second_child[1]->proba)+(current_node->second_child[0]->proba))){
                    next_node = current_node->second_child[1];
                }
                else{
                    next_node = current_node->second_child[2];
                }
                ClearBackground(RAYWHITE);
                drawBackground(font,background_texture);
                DrawTextBoxed(font, next_node->textAndOptions->text, (Rectangle){ container.x + 40, container.y + 50, container.width - 40, container.height - 50 }, 20.0f, 2.0f, wordWrap, customColor_darkBrown);
                displayOptions(next_node);

                current_node = next_node;
                if(next_node->first_child[0] == NULL && next_node->first_child[1] == NULL && next_node->first_child[2] == NULL && next_node->second_child[0] == NULL && next_node->second_child[1] == NULL && next_node->second_child[2] == NULL && next_node->third_child[0] == NULL && next_node->third_child[1] == NULL && next_node->third_child[2] == NULL && next_node->fourth_child[0] == NULL && next_node->fourth_child[1] == NULL && next_node->fourth_child[2] == NULL ){
                    end_game = true;
                }
            }   
       
       }
 
       else if (IsKeyPressed(KEY_UP)&(!welcome_page)) {
           first_event = false; 
           int random_number = rand()%100;      // Returns a pseudo-random integer between 0 and 99.
           
           if(current_node->third_child[0] == NULL){
               DrawTextBoxed(font, "this is not a valid option", (Rectangle){ container.x + 40, container.y + 270, container.width - 40, container.height - 270 }, 20.0f, 2.0f, wordWrap, customColor_darkBrown);
            }
            else{
                if (random_number < (current_node->third_child[0]->proba)){ 
                    next_node = current_node->third_child[0];            
                }
                else if((random_number) < ((current_node->third_child[1]->proba)+(current_node->third_child[0]->proba))){
                    next_node = current_node->third_child[1];
                }
                else{
                    next_node = current_node->third_child[2];
                }
                ClearBackground(RAYWHITE);
                drawBackground(font,background_texture);
                DrawTextBoxed(font, next_node->textAndOptions->text, (Rectangle){ container.x + 40, container.y + 50, container.width - 40, container.height - 50 }, 20.0f, 2.0f, wordWrap, customColor_darkBrown);
                displayOptions(next_node);

                current_node = next_node;
                if(next_node->first_child[0] == NULL && next_node->first_child[1] == NULL && next_node->first_child[2] == NULL && next_node->second_child[0] == NULL && next_node->second_child[1] == NULL && next_node->second_child[2] == NULL && next_node->third_child[0] == NULL && next_node->third_child[1] == NULL && next_node->third_child[2] == NULL && next_node->fourth_child[0] == NULL && next_node->fourth_child[1] == NULL && next_node->fourth_child[2] == NULL ){
                    end_game = true;
                }
            }   
       
       }
 
       else if (IsKeyPressed(KEY_DOWN)&(!welcome_page)) {
           first_event = false; 
           int random_number = rand()%100;      // Returns a pseudo-random integer between 0 and 99.
           
           if(current_node->fourth_child[0] == NULL){
               DrawTextBoxed(font, "this is not a valid option", (Rectangle){ container.x + 40, container.y + 270, container.width - 40, container.height - 270 }, 20.0f, 2.0f, wordWrap, customColor_darkBrown);
            }
            else{
                if (random_number < (current_node->fourth_child[0]->proba)){ 
                    next_node = current_node->fourth_child[0];            
                }
                else if((random_number) < ((current_node->fourth_child[1]->proba)+(current_node->fourth_child[0]->proba))){
                    next_node = current_node->fourth_child[1];
                }
                else{
                    next_node = current_node->fourth_child[2];
                }
                ClearBackground(RAYWHITE);
                drawBackground(font,background_texture);
                DrawTextBoxed(font, next_node->textAndOptions->text, (Rectangle){ container.x + 40, container.y + 50, container.width - 40, container.height - 50 }, 20.0f, 2.0f, wordWrap, customColor_darkBrown);
                displayOptions(next_node);

                current_node = next_node;
                if(next_node->first_child[0] == NULL && next_node->first_child[1] == NULL && next_node->first_child[2] == NULL && next_node->second_child[0] == NULL && next_node->second_child[1] == NULL && next_node->second_child[2] == NULL && next_node->third_child[0] == NULL && next_node->third_child[1] == NULL && next_node->third_child[2] == NULL && next_node->fourth_child[0] == NULL && next_node->fourth_child[1] == NULL && next_node->fourth_child[2] == NULL ){
                    end_game = true;
                }
            }          
       }

       else if (first_event){
           //display the first event, and its options
           ClearBackground(RAYWHITE);
           drawBackground(font,background_texture);
           DrawTextBoxed(font, current_node->textAndOptions->text, (Rectangle){ container.x + 40, container.y + 50, container.width - 40, container.height - 50 }, 20.0f, 2.0f, wordWrap, customColor_darkBrown);  
           displayOptions(current_node);

       }

       else if(end_game){
           DrawTextBoxed(font, "end of the game. Press the space bar to replay", (Rectangle){ container.x + 40, container.y + 200, container.width - 40, container.height - 200 }, 20.0f, 2.0f, wordWrap, customColor_darkBrown);
           
           if (IsKeyPressed(KEY_SPACE)){  //restarting the game:
               current_node = create_tree(root_node);
               welcome_page = true;
               end_game = false;
           }
       }

       else if(welcome_page){
           DrawTexture(welcome_page_texture, 0, 0, WHITE); 
            if (IsKeyPressed(KEY_SPACE)){ //starting the game
               first_event = true;
               welcome_page = false;
           }
       }
       

        BeginDrawing();
        EndDrawing();
   }
 
   // De-Initialization
   
   destroyTree(root_node);
   
   CloseWindow();
   
 
   return 0;
}

    
void drawBackground(Font font, Texture background_texture){
    DrawTexture(background_texture, 0, 0, WHITE);
    DrawTextBoxed(font, "press an arrow to play", (Rectangle){ container.x + 40, container.y + 290, container.width - 40, container.height - 290 }, 20.0f, 2.0f, wordWrap, customColor_darkBrown);
    
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
        DrawTextBoxed(font, option, (Rectangle){ container.x + 40, container.y + height, container.width - 40, container.height - height }, 20.0f, 2.0f, wordWrap, customColor_lightBrown);
    }

}

/*
The next functions are used to manage the tree
*/

textEvent *new_textEvent(char* text, char* option1, char* option2, char* option3, char* option4){
    textEvent *tmp = (struct textEvent *)malloc(sizeof(struct textEvent));
    tmp -> text = text;      
    tmp -> option1 = option1;     
    tmp -> option2 = option2;        
    tmp -> option3 = option3;     
    tmp -> option4 = option4;
    
    return tmp;
}


node *new_node_with_proba(textEvent* textAndOptions, int proba)
{
  node *tmp = (struct node *)malloc(sizeof(struct node));
  tmp->textAndOptions = textAndOptions;
  tmp->proba = proba;
  tmp->first_child[0] = NULL;
  tmp->first_child[1] = NULL;
  tmp->first_child[2] = NULL;
  tmp->second_child[0] = NULL;
  tmp->second_child[1] = NULL;
  tmp->second_child[2] = NULL;
  tmp->third_child[0] = NULL;
  tmp->third_child[1] = NULL;
  tmp->third_child[2] = NULL;
  tmp->fourth_child[0] = NULL;
  tmp->fourth_child[1] = NULL;
  tmp->fourth_child[2] = NULL;
  return tmp;
}
 
node* create_root_node( textEvent* textAndOptions) // inserting nodes!
{
  return new_node_with_proba(textAndOptions, 100);
}
 
 
node* insert_first_child(node* parent_node, textEvent* child_value, int proba, int position) // inserting nodes!
{
  parent_node->first_child[position] = new_node_with_proba(child_value, proba);
}
 
node* insert_second_child(node* parent_node, textEvent* child_value, int proba, int position) // inserting nodes!
{
  parent_node->second_child[position] = new_node_with_proba(child_value, proba);
}
 
node* insert_third_child(node* parent_node, textEvent* child_value, int proba, int position) // inserting nodes!
{
  parent_node->third_child[position] = new_node_with_proba(child_value, proba);
}
 
node* insert_fourth_child(node* parent_node, textEvent* child_value, int proba, int position) // inserting nodes!
{
  parent_node->fourth_child[position] = new_node_with_proba(child_value, proba);
}
 
 
node * create_tree(node *root_node)
{
   node * node_B = insert_first_child(root_node, new_textEvent("Node B, first child node of A", "B opt1", "B opt2", "B opt3", "B opt4"), 40, 0);
   node * node_C = insert_first_child(root_node, new_textEvent("Node C, second child node of A","C opt1", NULL, NULL, NULL),60,1);  
   node * node_D = insert_second_child(root_node, new_textEvent("Node D, first child node of A","D opt1", NULL, NULL, NULL), 100, 0);
   node * node_E = insert_third_child(root_node, new_textEvent("Node E, second child node of A",NULL, NULL, NULL, NULL), 50,0);   
   node * node_F = insert_third_child(root_node, new_textEvent("Node F, first child node of D",NULL, NULL, NULL, NULL),50,1);
   node * node_G = insert_fourth_child(root_node, new_textEvent("Node G, second child node of D",NULL, NULL, NULL, NULL),100,0);

   node * node_H = insert_first_child(node_B, new_textEvent("Node H, first child node of C",NULL, NULL, NULL, NULL),30,0);
   node * node_I = insert_first_child(node_B, new_textEvent("Node I, second child node of C",NULL, NULL, NULL, NULL),30,1);   
   node * node_J = insert_first_child(node_B, new_textEvent("Node J, 3rd child node of A",NULL, NULL, NULL, NULL),40,2);

   node * node_M = insert_second_child(node_B, new_textEvent("Node M, 1th child node of J","option1", NULL, NULL, NULL),50,0);
   node * node_N = insert_second_child(node_B, new_textEvent("Node N, 1th child node of J","option1", NULL, NULL, NULL),50,1);

   node * node_K = insert_first_child(node_G, new_textEvent("Node K, 4th child node of A",NULL, NULL, NULL, NULL),20,0);
   node * node_L = insert_first_child(node_G, new_textEvent("Node L, 1th child node of J",NULL, NULL, NULL, NULL),80,1);



   return root_node;
}

void destroyTree(node * node){
    if (node==NULL) return;
    destroyTree(node->first_child[0]);
    destroyTree(node->first_child[1]);
    destroyTree(node->first_child[2]);
    destroyTree(node->second_child[0]);
    destroyTree(node->second_child[1]);
    destroyTree(node->second_child[2]);
    destroyTree(node->third_child[0]);
    destroyTree(node->third_child[1]);
    destroyTree(node->third_child[2]);
    destroyTree(node->fourth_child[0]);
    destroyTree(node->fourth_child[1]);
    destroyTree(node->fourth_child[2]);

    free(node->textAndOptions);
    free(node);
}


    

// The next two functions were taken from the raylib example entitled "text_rectangle_bounds", by SzieberthAdam.
// It can be found here : https://github.com/raysan5/raylib/blob/master/examples/text/text_rectangle_bounds.c
// It is used to keep the text inside the screen.
 
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
 
 
 
 

