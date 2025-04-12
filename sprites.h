byte wall[54] = { 234, 234, 233, 193, 194, 195, 224, 192, 192, 196, 192, 201, 224, 192, 192, 208, 208, 193, 224, 192, 192, 192, 193, 193, 224, 192, 192, 200, 224, 201, 224, 192, 192, 192, 193, 195, 224, 192, 192, 192, 208, 193, 224, 192, 192, 200, 193, 197, 224, 192, 192, 234, 234, 234 };
byte block1[54] = { 192, 78, 192, 113, 90, 65, 110, 118, 125, 111, 85, 77, 109, 117, 123, 110, 117, 67, 87, 82, 125, 123, 109, 69, 100, 76, 125, 123, 82, 75, 86, 115, 119, 109, 117, 91, 107, 101, 93, 107, 85, 109, 110, 125, 117, 105, 90, 125, 99, 103, 65, 192, 127, 192 };
byte timer[54] = { 64, 64, 64, 64, 94, 64, 64, 76, 64, 71, 94, 120, 79, 97, 124, 94, 68, 94, 93, 64, 110, 68, 96, 72, 72, 80, 68, 74, 76, 68, 72, 76, 84, 72, 68, 68, 68, 68, 72, 69, 64, 104, 66, 68, 80, 71, 97, 120, 78, 94, 92, 64, 64, 64 };
byte heart[54] = { 64, 64, 64, 64, 64, 64, 64, 64, 64, 71, 64, 120, 79, 97, 124, 95, 115, 126, 95, 127, 126, 95, 127, 126, 95, 246, 126, 79, 127, 124, 79, 254, 124, 71, 127, 120, 67, 200, 112, 65, 127, 96, 64, 127, 64, 64, 94, 64, 64, 76, 64, 64, 64, 64 };
byte joker[54] = { 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 76, 64, 64, 127, 64, 65, 196, 96, 65, 208, 96, 67, 224, 112, 67, 194, 112, 65, 200, 96, 65, 194, 96, 64, 127, 64, 64, 76, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64 };

byte blue_walk_left[162] = { 64,64,64,66,99,112,65,127,112,65,222,96,66,64,112,71,223,72,70,96,120,75,255,68,74,64,124,75,255,68,74,96,124,71,223,72,68,64,120,66,255,80,65,97,96,67,127,96,67,113,80,64,64,64,64,64,64,67,112,74,67,119,124,64,231,88,64,96,124,65,199,66,65,104,126,66,207,254,66,96,65,66,207,254,66,104,65,65,199,253,65,64,126,64,223,68,64,88,120,64,127,111,65,80,79,64,64,64,64,64,64,84,67,112,79,123,112,70,249,64,72,65,64,94,255,96,90,64,96,211,255,80,104,64,112,211,255,80,106,64,112,94,255,96,80,64,96,72,254,64,71,70,64,125,127,64,124,66,96,64,64,64 };
byte blue_walk_right[162] = { 64,64,64,66,99,112,65,127,112,65,254,96,67,64,112,68,254,120,71,65,88,72,255,116,79,64,84,72,255,116,79,65,84,68,254,120,71,64,72,66,255,80,65,97,96,67,127,96,67,113,80,64,64,64,64,64,64,67,112,74,67,119,124,64,231,88,64,96,68,65,255,94,65,64,86,66,255,242,67,64,69,66,255,242,67,64,85,65,255,94,65,64,66,64,223,68,64,88,120,64,127,111,65,80,79,64,64,64,64,64,64,84,67,112,79,123,112,70,249,64,79,65,64,80,248,96,95,69,96,223,252,80,96,65,80,223,252,80,96,69,80,239,248,96,95,64,96,72,254,64,71,70,64,125,127,64,124,66,96,64,64,64 };
byte blue_walk_down[162] = { 64, 64, 64, 64, 64, 64, 64, 94, 64, 65, 222, 96, 83, 64, 118, 76, 255, 78, 95, 64, 126, 72, 255, 70, 79, 64, 124, 72, 255, 68, 95, 64, 124, 92, 206, 110, 92, 106, 108, 90, 196, 114, 65, 97, 96, 64, 94, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 88, 94, 64, 89, 222, 98, 91, 64, 116, 92, 255, 78, 71, 64, 124, 72, 255, 68, 79, 64, 124, 72, 255, 68, 79, 64, 124, 77, 220, 72, 93, 85, 78, 75, 200, 86, 81, 97, 102, 64, 94, 70, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 94, 70, 81, 222, 102, 75, 64, 118, 92, 255, 78, 79, 64, 120, 72, 255, 68, 79, 64, 124, 72, 255, 68, 79, 64, 124, 68, 206, 108, 92, 106, 110, 90, 196, 116, 89, 97, 98, 88, 94, 64, 64, 64, 64, 64, 64, 64 };
byte blue_walk_up[162] = { 64, 64, 64, 64, 64, 64, 64, 94, 64, 65, 97, 96, 83, 196, 118, 76, 213, 110, 94, 113, 110, 72, 255, 70, 79, 64, 124, 72, 255, 68, 95, 64, 124, 92, 255, 78, 95, 64, 124, 90, 255, 114, 65, 97, 96, 64, 94, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 88, 94, 64, 89, 97, 98, 91, 200, 84, 93, 234, 78, 69, 99, 92, 72, 255, 68, 79, 64, 124, 72, 255, 68, 79, 64, 124, 76, 255, 72, 95, 64, 126, 75, 255, 118, 81, 97, 102, 64, 94, 70, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 94, 70, 81, 97, 102, 75, 196, 118, 92, 213, 110, 78, 113, 104, 72, 255, 68, 79, 64, 124, 72, 255, 68, 79, 64, 124, 68, 255, 76, 95, 64, 126, 90, 255, 116, 89, 97, 98, 88, 94, 64, 64, 64, 64, 64, 64, 64 };
byte blue_stay[54] = { 64, 64, 64, 64, 64, 64, 64, 94, 64, 65, 222, 96, 67, 64, 112, 69, 222, 104, 69, 82, 104, 73, 204, 100, 95, 64, 126, 88, 255, 70, 95, 64, 126, 84, 243, 74, 118, 82, 91, 106, 255, 85, 65, 97, 96, 71, 94, 120, 79, 97, 124, 64, 64, 64 };
byte blue_sleep[54] = { 64, 65, 119, 64, 64, 98, 64, 95, 119, 65, 222, 96, 67, 64, 127, 68, 255, 74, 68, 115, 76, 73, 255, 103, 76, 64, 76, 88, 255, 70, 92, 64, 78, 84, 241, 74, 86, 64, 90, 114, 255, 83, 105, 97, 101, 65, 94, 96, 71, 64, 120, 79, 97, 124 };

byte red_walk_left[162] = { 64,64,64,66,99,112,65,127,112,65,97,96,66,255,80,71,96,120,70,223,72,75,64,124,74,255,68,75,64,124,74,223,68,71,96,120,68,255,72,66,64,112,65,255,96,67,127,96,67,113,80,64,64,64,64,64,64,67,112,74,67,119,124,64,88,120,64,223,68,65,64,126,65,199,254,66,104,65,66,207,254,66,96,65,66,207,254,65,104,126,65,199,66,64,96,124,64,239,88,64,127,111,65,80,79,64,64,64,64,64,64,84,67,112,79,123,112,70,70,64,72,255,64,88,64,96,209,255,96,106,64,112,211,255,80,104,64,112,211,255,80,90,64,96,94,255,96,72,65,64,70,253,64,125,127,64,124,66,96,64,64,64 };
byte red_walk_right[162] = { 64,64,64,66,99,112,65,127,112,65,97,96,66,255,80,71,65,120,68,254,88,79,64,116,72,255,84,79,64,116,72,254,84,71,65,120,68,255,72,67,64,112,65,255,96,67,127,96,67,113,80,64,64,64,64,64,64,67,112,74,67,119,124,64,88,120,64,255,68,65,64,94,65,255,226,66,64,85,66,255,242,66,64,69,66,255,242,65,64,86,65,255,94,64,96,68,64,239,88,64,127,111,65,80,79,64,64,64,64,64,64,84,67,112,79,123,112,70,70,64,72,255,64,95,64,96,223,248,96,96,69,80,223,252,80,96,65,80,223,252,80,95,69,96,80,248,96,79,65,64,70,253,64,125,127,64,124,66,96,64,64,64 };
byte red_walk_down[162] = { 64, 64, 64, 64, 64, 64, 64, 94, 64, 65, 97, 96, 82, 255, 86, 79, 64, 126, 92, 255, 78, 79, 64, 126, 72, 255, 68, 79, 64, 124, 89, 220, 68, 93, 85, 94, 93, 192, 76, 90, 64, 82, 65, 255, 96, 64, 94, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 88, 94, 64, 89, 97, 98, 90, 255, 84, 95, 64, 126, 68, 255, 76, 79, 64, 124, 72, 255, 68, 79, 64, 124, 72, 206, 100, 78, 106, 104, 92, 192, 110, 75, 64, 118, 81, 255, 102, 64, 94, 70, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 94, 70, 81, 97, 102, 74, 255, 86, 95, 64, 126, 76, 255, 72, 79, 64, 124, 72, 255, 68, 78, 64, 124, 77, 220, 68, 69, 85, 92, 93, 192, 78, 90, 64, 84, 89, 255, 98, 88, 94, 64, 64, 64, 64, 64, 64, 64 };
byte red_walk_up[162] = { 64, 64, 64, 64, 64, 64, 64, 94, 64, 65, 97, 96, 82, 255, 86, 77, 119, 94, 93, 85, 78, 77, 220, 94, 72, 255, 68, 79, 64, 124, 88, 255, 68, 95, 64, 126, 92, 255, 76, 90, 64, 82, 65, 222, 96, 64, 94, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 88, 94, 64, 89, 97, 98, 90, 255, 84, 94, 123, 110, 68, 106, 108, 78, 206, 108, 72, 255, 68, 79, 64, 124, 72, 255, 68, 79, 64, 120, 92, 255, 78, 75, 64, 118, 81, 222, 102, 64, 94, 70, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 94, 70, 81, 97, 102, 74, 255, 86, 93, 119, 94, 77, 85, 72, 77, 220, 92, 72, 255, 68, 79, 64, 124, 76, 255, 68, 71, 64, 124, 92, 255, 78, 90, 64, 84, 89, 222, 98, 88, 94, 64, 64, 64, 64, 64, 64, 64 };
byte red_stay[54] = { 64, 64, 64, 64, 64, 64, 64, 94, 64, 65, 97, 96, 66, 255, 80, 68, 64, 72, 69, 222, 104, 77, 82, 108, 73, 204, 100, 94, 64, 94, 92, 255, 70, 87, 76, 122, 84, 237, 90, 114, 64, 83, 105, 255, 101, 65, 94, 96, 71, 64, 120, 79, 97, 124 };
byte red_sleep[54] = { 64, 65, 119, 64, 64, 98, 64, 95, 119, 65, 97, 96, 66, 255, 95, 68, 64, 74, 68, 255, 76, 76, 115, 71, 73, 255, 100, 92, 64, 70, 92, 255, 70, 84, 78, 74, 84, 255, 74, 114, 64, 83, 105, 255, 101, 65, 94, 96, 71, 64, 120, 79, 97, 124 };

byte green_walk_left[162] = { 64,64,64,66,99,112,65,127,112,65,127,96,67,127,112,68,79,120,69,119,120,73,87,124,75,111,124,74,79,124,75,111,124,69,87,120,69,119,120,66,79,112,65,127,96,67,127,96,67,113,80,64,64,64,64,64,64,67,112,74,67,119,126,64,95,120,64,99,124,65,93,126,65,85,126,66,123,127,66,99,127,66,123,127,66,85,127,65,93,126,65,65,126,64,127,124,64,95,120,64,127,111,65,80,79,64,64,64,64,64,64,84,67,112,79,123,112,71,126,64,79,127,64,80,127,96,87,95,96,101,95,112,110,127,112,104,127,112,110,127,112,85,95,96,87,95,96,72,127,64,71,126,64,125,127,64,124,66,96,64,64,64 };
byte green_walk_right[162] = { 64,64,64,66,99,112,65,127,112,65,127,96,67,124,80,71,123,104,71,122,104,79,125,116,79,124,84,79,125,116,79,122,100,71,123,104,71,124,72,67,127,112,65,127,96,67,127,96,67,113,80,64,64,64,64,64,64,67,112,74,67,119,126,64,95,120,64,127,124,65,127,66,65,126,122,67,126,105,67,127,93,67,127,69,67,127,93,65,126,106,65,126,122,64,127,68,64,95,120,64,127,111,65,80,79,64,64,64,64,64,64,84,67,112,79,123,112,71,126,64,79,113,64,95,110,96,95,106,96,127,119,80,127,113,80,127,119,80,127,106,80,95,110,96,95,112,96,79,127,64,71,126,64,125,127,64,124,66,96,64,64,64 };
byte green_walk_down[162] = { 64, 64, 64, 64, 64, 64, 64, 94, 64, 65, 127, 96, 83, 127, 118, 79, 127, 126, 95, 127, 126, 79, 127, 126, 79, 127, 124, 79, 78, 92, 94, 113, 108, 94, 106, 110, 94, 123, 108, 90, 94, 82, 65, 97, 96, 64, 94, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 88, 94, 64, 89, 127, 98, 91, 127, 116, 95, 127, 126, 71, 127, 124, 79, 127, 124, 79, 127, 124, 78, 92, 124, 77, 99, 92, 77, 85, 88, 93, 119, 94, 74, 94, 86, 81, 97, 102, 64, 94, 70, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 94, 70, 81, 127, 102, 75, 127, 118, 95, 127, 126, 71, 127, 120, 71, 127, 124, 71, 127, 124, 71, 78, 92, 70, 113, 108, 66, 106, 108, 94, 123, 110, 90, 94, 84, 89, 97, 98, 88, 95, 64, 64, 64, 64, 64, 64, 64 };
byte green_walk_up[162] = { 64, 64, 64, 64, 64, 64, 64, 94, 64, 65, 97, 96, 82, 94, 86, 78, 123, 110, 94, 106, 110, 78, 113, 110, 79, 78, 92, 79, 127, 124, 95, 127, 124, 95, 127, 126, 95, 127, 124, 91, 127, 114, 65, 127, 96, 64, 94, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 88, 94, 64, 89, 97, 98, 90, 94, 84, 93, 119, 94, 69, 85, 92, 77, 99, 92, 78, 92, 124, 79, 127, 124, 79, 127, 124, 79, 127, 120, 95, 127, 126, 75, 127, 118, 81, 127, 102, 64, 94, 70, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 94, 70, 81, 97, 102, 74, 94, 86, 94, 123, 110, 70, 106, 104, 70, 113, 108, 71, 78, 92, 71, 127, 124, 71, 127, 124, 67, 127, 124, 95, 127, 126, 91, 127, 116, 89, 127, 98, 88, 94, 64, 64, 64, 64, 64, 64, 64 };
byte green_stay[54] = { 64, 64, 64, 64, 64, 64, 64, 94, 64, 65, 109, 96, 67, 97, 112, 69, 82, 104, 69, 115, 104, 78, 76, 92, 79, 127, 124, 95, 127, 126, 95, 115, 126, 87, 109, 122, 87, 127, 122, 115, 127, 115, 105, 127, 101, 65, 94, 96, 71, 64, 120, 79, 97, 124 };
byte green_sleep[54] = { 64, 65, 119, 64, 64, 98, 64, 95, 119, 65, 127, 96, 67, 127, 127, 71, 78, 90, 70, 127, 108, 79, 127, 127, 79, 127, 124, 95, 127, 126, 95, 127, 126, 87, 112, 122, 87, 127, 122, 115, 127, 115, 105, 127, 101, 65, 94, 96, 71, 64, 120, 79, 97, 124 };

byte yellow_walk_left[162] = { 64,64,64,66,99,112,65,127,112,65,127,96,66,64,80,71,111,120,70,96,72,75,95,124,74,64,68,75,95,124,74,96,68,71,111,120,68,64,72,67,127,112,65,97,96,67,127,96,67,113,80,64,64,64,64,64,64,67,112,74,67,119,124,64,95,120,64,96,68,65,123,126,65,104,66,66,119,127,66,96,65,66,119,127,66,104,65,65,123,126,65,64,66,64,127,124,64,88,88,64,127,111,65,80,79,64,64,64,64,64,64,84,67,112,79,123,112,71,126,64,72,65,64,94,127,96,90,64,96,109,127,112,96,64,80,109,127,112,106,64,80,94,127,96,80,64,96,79,127,64,70,70,64,125,127,64,124,66,96,64,64,64 };
byte yellow_walk_right[162] = { 64,64,64,66,99,112,65,127,112,65,127,96,66,64,80,71,125,120,68,65,88,79,126,116,72,64,84,79,126,116,72,65,84,71,125,120,68,64,72,67,127,112,65,97,96,67,127,96,67,113,80,64,64,64,64,64,64,67,112,74,67,119,124,64,95,120,64,96,68,65,127,94,65,64,86,67,127,109,66,64,69,67,127,109,66,64,85,65,127,94,65,64,66,64,127,124,64,88,88,64,127,111,65,80,79,64,64,64,64,64,64,84,67,112,79,123,112,71,126,64,72,65,64,95,119,96,80,69,96,127,123,80,96,65,80,127,123,80,96,69,80,95,119,96,80,64,96,79,127,64,70,70,64,125,127,64,124,66,96,64,64,64 };
byte yellow_walk_down[162] = { 64, 64, 64, 64, 64, 64, 64, 94, 64, 65, 127, 96, 82, 64, 86, 79, 127, 126, 92, 64, 78, 79, 127, 126, 72, 64, 68, 79, 127, 124, 88, 64, 68, 94, 113, 110, 92, 106, 108, 90, 123, 114, 65, 97, 96, 64, 94, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 88, 94, 64, 89, 127, 98, 90, 64, 84, 95, 127, 126, 68, 64, 76, 79, 127, 124, 72, 64, 68, 79, 127, 124, 72, 64, 68, 77, 99, 88, 93, 85, 78, 75, 119, 86, 81, 97, 102, 64, 94, 70, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 94, 70, 81, 127, 102, 74, 64, 86, 95, 127, 126, 76, 64, 72, 79, 127, 124, 72, 64, 68, 79, 127, 124, 72, 64, 68, 70, 113, 108, 92, 106, 110, 90, 123, 116, 89, 97, 98, 88, 94, 64, 64, 64, 64, 64, 64, 64 };
byte yellow_walk_up[162] = { 64, 64, 64, 64, 64, 64, 64, 94, 64, 65, 127, 96, 82, 64, 86, 78, 123, 110, 92, 106, 110, 78, 113, 110, 72, 68, 68, 79, 127, 124, 88, 64, 68, 95, 127, 126, 92, 64, 76, 91, 127, 114, 65, 97, 96, 64, 94, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 88, 94, 64, 89, 127, 98, 90, 64, 84, 93, 119, 94, 69, 85, 76, 77, 99, 92, 72, 72, 68, 79, 127, 124, 72, 64, 68, 79, 127, 120, 92, 64, 78, 75, 127, 118, 81, 97, 102, 64, 94, 70, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 94, 70, 81, 127, 102, 74, 64, 86, 94, 123, 110, 76, 106, 104, 78, 113, 108, 72, 68, 68, 79, 127, 124, 72, 64, 68, 71, 127, 124, 92, 64, 78, 91, 127, 116, 89, 97, 98, 88, 94, 64, 64, 64, 64, 64, 64, 64 };
byte yellow_stay[54] = { 64, 64, 64, 64, 64, 64, 64, 94, 64, 65, 127, 96, 66, 76, 80, 69, 97, 104, 69, 82, 104, 73, 127, 100, 72, 64, 68, 95, 115, 126, 88, 76, 70, 87, 82, 122, 84, 64, 74, 115, 127, 115, 105, 97, 101, 65, 94, 96, 71, 64, 120, 79, 97, 124 };
byte yellow_sleep[54] = { 64, 65, 119, 64, 64, 98, 64, 95, 119, 65, 127, 96, 66, 115, 95, 71, 76, 122, 68, 76, 76, 78, 127, 111, 72, 64, 68, 95, 127, 126, 88, 94, 70, 87, 97, 122, 84, 94, 74, 115, 127, 115, 105, 97, 101, 65, 94, 96, 71, 64, 120, 79, 97, 124 };

byte blue_exit[54] = { 64, 64, 64, 64, 64, 64, 64, 94, 64, 65, 192, 96, 67, 192, 112, 71, 204, 120, 71, 97, 120, 79, 255, 124, 79, 64, 124, 79, 255, 124, 79, 97, 124, 71, 204, 120, 71, 192, 120, 67, 192, 112, 65, 127, 96, 64, 94, 64, 64, 64, 64, 64, 64, 64 };
byte red_exit[54] = { 64, 64, 64, 64, 64, 64, 64, 94, 64, 65, 192, 96, 67, 192, 112, 71, 192, 120, 71, 222, 120, 79, 64, 124, 79, 255, 124, 79, 64, 124, 79, 222, 124, 71, 192, 120, 71, 192, 120, 67, 127, 112, 65, 192, 96, 64, 94, 64, 64, 64, 64, 64, 64, 64 };
byte yellow_exit[54] = { 64, 64, 64, 64, 64, 64, 64, 94, 64, 65, 97, 96, 66, 64, 80, 68, 76, 72, 68, 82, 72, 72, 127, 68, 72, 97, 68, 72, 127, 68, 72, 82, 68, 68, 76, 72, 68, 64, 72, 67, 64, 112, 65, 97, 96, 64, 94, 64, 64, 64, 64, 64, 64, 64 };
byte green_exit[54] = { 64, 64, 64, 64, 64, 64, 64, 94, 64, 65, 97, 96, 66, 64, 80, 68, 64, 72, 68, 76, 72, 72, 94, 68, 72, 127, 68, 72, 127, 68, 72, 94, 68, 68, 76, 72, 68, 64, 72, 66, 64, 80, 65, 97, 96, 64, 94, 64, 64, 64, 64, 64, 64, 64 };

byte clean[54] = { 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64 };

byte bravo[200] = { 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 67, 96, 64, 64, 64, 64, 64, 64, 64, 64, 64, 120, 64, 64, 64, 64, 64, 64, 64, 64, 64, 100, 64, 64, 64, 64, 64, 64, 64, 64, 65, 66, 64, 64, 64, 64, 64, 64, 64, 64, 65, 66, 64, 64, 64, 64, 64, 78, 68, 64, 65, 68, 64, 64, 64, 64, 80, 81, 72, 64, 65, 120, 66, 120, 94, 80, 107, 112, 112, 64, 66, 71, 65, 68, 98, 80, 92, 105, 80, 64, 66, 64, 97, 65, 66, 72, 73, 70, 80, 64, 66, 64, 97, 65, 66, 72, 73, 64, 72, 64, 66, 64, 81, 66, 66, 68, 81, 64, 72, 64, 66, 64, 81, 66, 66, 68, 81, 64, 72, 64, 66, 64, 98, 65, 70, 66, 96, 96, 80, 64, 66, 65, 66, 64, 122, 65, 64, 88, 96, 64, 95, 126, 64, 64, 65, 96, 64, 71, 64, 64 };
byte youwon[100] = { 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 80, 80, 64, 64, 64, 64, 64, 64, 72, 64, 80, 99, 99, 68, 68, 76, 121, 112, 72, 64, 72, 100, 95, 68, 68, 78, 102, 94, 72, 64, 68, 103, 120, 100, 68, 101, 122, 73, 72, 64, 67, 68, 68, 100, 66, 117, 66, 73, 72, 64, 65, 68, 68, 100, 67, 73, 66, 73, 72, 64, 65, 66, 72, 108, 67, 73, 66, 73, 64, 64, 65, 65, 112, 91, 66, 80, 124, 73, 72, 64, 65, 64, 64, 64, 64, 64, 64, 64, 64, 64 };
byte tryagain[100] = { 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 95, 96, 64, 64, 64, 64, 72, 64, 80, 64, 68, 64, 64, 70, 67, 76, 65, 64, 80, 64, 68, 84, 102, 65, 68, 98, 72, 120, 80, 64, 66, 90, 100, 71, 68, 103, 72, 100, 80, 64, 66, 80, 92, 73, 67, 105, 68, 100, 80, 64, 66, 72, 68, 73, 64, 105, 68, 100, 80, 64, 66, 72, 68, 70, 112, 102, 100, 98, 64, 64, 64, 64, 88, 64, 71, 64, 64, 64, 80, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64 };
byte youlost[100] = { 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 80, 80, 64, 64, 72, 64, 64, 80, 72, 64, 80, 99, 99, 68, 68, 88, 108, 80, 72, 64, 72, 100, 95, 68, 68, 103, 80, 124, 72, 64, 68, 103, 120, 100, 68, 124, 72, 80, 72, 64, 67, 68, 68, 100, 68, 98, 68, 80, 72, 64, 65, 68, 68, 100, 68, 98, 66, 80, 72, 64, 65, 66, 72, 108, 68, 82, 82, 80, 64, 64, 65, 65, 112, 91, 66, 76, 76, 76, 72, 64, 65, 64, 64, 64, 64, 64, 64, 64, 64, 64 };
