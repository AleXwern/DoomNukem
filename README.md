# DoomNukem
Hive Helsinki project DoomNukem by anystrom, tbergkul and vkeinane
Final score 123/100

# How to use -> UNIX:
1. Compile game with 'make' and run ./doom-nukem
2. Compile server with 'make server' and run ./doom-server

# How to use -> WIN64:
1. Soon! It exists but needs some nice and user friendly way to compile (low-prio atm)
2. Before that you can get a Windows version in Release tab although it can be outdated.

# Controls

General
1. ESC - Go back to main menu. If in main menu, close the game

Game
1. Arrowkeys - Turn camera
2. WS - Move front/back
3. AD - Strafe left/right
4. Space - Jump
5. C - Crouch
6. Shift - Sprint
7. T - Turn textures on and off
8. R - Reload the gun if you have one
9. 1 and 2 - Jetpack down/up
10. L - Set block oulines on/off
11. M - Open/close options menu
12. Mouse left - Shoot with gun if you have one
13. Mouse right - Interact with an object in front of you
14. Mouse middle - (De)activate mouse focus
15. Secret - Invincibility

Menus (main/game/editor menus)
1. Arrow up/down - Scroll options
2. Arrow left/right - Increase/decrease value
3. Space - Select current option (main menu)
4. Space - Set value to min/max

Editor
1. S - Save the map
2. Mouse left - Change values (block and metadata)
3. Mouse right - Copy block data to current "pencil"
4. 12 - Change between block and sprite edit tabs

# Connecting to server
1. Start game and in-game open menu (M)
2. "Connect" -> Right to connect, left to disconnect
3. If you exit the game, go to main menu or the server doesn't exist you'll be disconnected automatically.
4. Server IP by default is HIVE c3r1p1 but you can change it in the includes/values.h -> #define IP (find the one that fits your OS)
