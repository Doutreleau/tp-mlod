
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

static void DrawTextBoxed(Font font, const char *text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint);

static void DrawTextBoxedSelectable(Font font, const char *text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint, int selectStart, int selectLength, Color selectTint, Color selectBackTint);


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

    //used to make sure the text stays in the screen
    Rectangle container = { 25.0f, 25.0f, screenWidth , screenHeight  };
    bool wordWrap = true;
    Font font = GetFontDefault(); 

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
            DrawTextBoxed(font, current_node->value, (Rectangle){ container.x + 4, container.y + 50, container.width - 4, container.height - 50 }, 20.0f, 2.0f, wordWrap, GRAY);
            
        }
        

        else if (choose_left)
        {
            next_node = current_node->left_child;
            if (next_node !=NULL){
                ClearBackground(RAYWHITE);
                DrawTextBoxed(font, next_node->value, (Rectangle){ container.x + 4, container.y + 50, container.width - 4, container.height - 50 }, 20.0f, 2.0f, wordWrap, GRAY);

                current_node = next_node;
                choose_left = false;
                if(next_node->left_child == NULL && next_node->right_child==NULL){
                    ClearBackground(RAYWHITE);
                    DrawTextBoxed(font, "end of the game", (Rectangle){ container.x + 4, container.y + 200, container.width - 4, container.height - 200 }, 20.0f, 2.0f, wordWrap, GRAY);

                }
            }
            else{
                ClearBackground(RAYWHITE);
                DrawTextBoxed(font, "end of the game", (Rectangle){ container.x + 4, container.y + 200, container.width - 4, container.height - 200 }, 20.0f, 2.0f, wordWrap, GRAY);

            }
        }

        
        else if (choose_right) {
            next_node = current_node->right_child;
            if (next_node !=NULL){
                ClearBackground(RAYWHITE);
                DrawTextBoxed(font, next_node->value, (Rectangle){ container.x + 4, container.y + 50, container.width - 4, container.height - 50 }, 20.0f, 2.0f, wordWrap, GRAY);
                current_node = next_node;
                choose_right = false;
                if(next_node->left_child == NULL && next_node->right_child==NULL){
                    ClearBackground(RAYWHITE);
                    DrawTextBoxed(font, "end of the game", (Rectangle){ container.x + 4, container.y + 200, container.width - 4, container.height - 200 }, 20.0f, 2.0f, wordWrap, GRAY);

                }
            }
            else{
                ClearBackground(RAYWHITE);
                DrawTextBoxed(font, "end of the game", (Rectangle){ container.x + 4, container.y + 200, container.width - 4, container.height - 200 }, 20.0f, 2.0f, wordWrap, GRAY);

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
    node * node_E = insert_right_node(node_B, "Node E, right child node of B"); 
    node * node_F = insert_left_node(node_D, "Node F, left child node of D"); 
    node * node_G = insert_right_node(node_D, "Node G, right child node of D"); 
    node * node_H = insert_left_node(node_C, "Node H, left child node of C"); 
    node * node_I = insert_right_node(node_C, "Node I, right child node of C"); 
 
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
