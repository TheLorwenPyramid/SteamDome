# SteamDome
SteamDome is an experimental modular Steamworks API wrapper for Unreal Engine 5 with support for C++ and Blueprints.

> [!Warning]
> This project it is in experimental stages, therefore, many things are untested and incomplete.

## Project structure
Each Steamworks API interface is its own plugin in the `Plugins/` folder.

Common structures shared between plugins are stored in the `SteamDomeCommon` plugin,
that should always be enabled when enabling any interface.

Additionally, the project includes UI elements and logic to test each method when possible.

## Progress
### SteamApps
All (non-obsolete) methods are implemented, only missing testing.

### SteamFriends
Work-in-progress...
More than half of the methods are complete, also missing all async methods.

