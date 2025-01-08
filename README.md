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

## The spirit of the License
Although I am not a lawyer, I created a modified version of the AAL license to use for this project.

The spirit of the license is:
- You are free to use the plugin and the example project for your game (commercial or not), given that you
  provide attribution in a prominent place in a splash-screen if possible, otherwise choose a place that is visible
  for all users.
- You can fork and modify the source code, given that you also provide attribution, maintain the same license,
  and provide your source code for free (if publicly distributed). If you modify the source code and keep your
  modifications private, you can. What you can not do, is offer the source code for money (even for modified versions).

If you have any questions, please contact me on <support@lorwenpyramid.com>.

_The full license is available in the LICENSE file_
