# TurboTribble
Engine for the Videogame Engines subject imparted in the Videogame Design and Development degree of CITM-UPC.

You can check more about the TurboTribble engine [here!](https://github.com/FireAlfa/TurboTribble)


 ## Members 
 * [Òscar Canales](https://github.com/Osvak)
 * [Carles Garriga](https://github.com/FireAlfa)

## Controls

- Right click + WASD: Move the camera in it's own axis.
- Right click + Q/E: Move the camera up or down in it's own axis.
- Mouse scroll wheel: Move the camera forward and backwards in it's own axis.
- While selecting a GameObject and holding Alt + left click: Orbit the camera around the GameObject.
- While selecting a GameObject and pressing F: Focus the GameObject.
- Key T: Reset the camera (World axis reset).
- Right click GameObject in the hierarchy: Open GameObject options.
- Supr while a GameObject is selected: Delete the GameObject.
- Supr while a resource is selected: Delete the resource.
- Hold left click in the hierarchy menu: Move GameObjects in the hierarchy (Reparenting).
- W,E,R buttons: show Move, Scale, Rotate guizmos. 
- Ctrl + N: Generate a new scene (You will be warned to save your current project).
- Ctrl + O: Opens the explorer window to search for a file and open it.
- Ctrl + S: Saves the current Scene.
- Ctrl + Shift + S: Opens the explorer window to save the scene in a desired location.
- Ctrl + D: Duplicates the selected game object.

- Play/Stop/Pause and Advance frame: To start a game preview, hit the play button, when you hit the play button, the preview will start, and the play button will be swapped by
the stop button. Hitting the stop button will stop the game preview.
Pause button will pause the game preview until you hit it again. When having the game in pause, you can advance one frame if you want. Also, the buttons and the whole engine will have different UI colors to let the user know that he is in game preview mode.

## Features

- Stencil border for the selected GameObject.
- Raycasting objects to select them (MousePicking).
- MousePicking detects the closest target that is hit.
- Resource manager that manages all kinds of resources, with a cool design.
  - All files are shown in the resource manager.
  - You can import any asset you need in it.
  - For better user experience, the resource has icons for models, folders, textures...
- Play/Stop/Pause and Advance next frame for game mode.
- Own file formats, hidden in the Engine's background.
  - They are saved as .rgtexture, .rgmesh and .rgmodel.
  - The scenes are saved as .ragnar.
  - The user will see the file formats as the ones he/she imported (png, jpg...).
- Selected GameObjects have Guizmos for better user experience.
- Imported texture and model options and filters (Alienify, flip UVs, Gaussian Blur...)
- Game clock and Engine clock.
- Quadtree implementation for better optimization.
- Camera system (Camera component, FOV, planes, etc...).
- Mini viewer to see what the game camera is looking at in the editor view.
  - Must have the camera selected, and it will be show in the bottom right corner of the editor viewport. 
- Different viewports (Editor View and Game View).
- Correct serialization and load methods for the engine.
- Frustum Culling for the cameras.
- AABB system for all the GameObjects.
- Shortcuts and explorer viewer for save, load and open files for better user experience.


## References

The base project is taken from [Ragnar Engine](https://github.com/UriKurae/Ragnar-Engine) by UriKurae

## License

MIT License

Copyright (c) 2022 Òscar Canales and Carles Garriga

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
