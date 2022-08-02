# Visual Novel Machinery Spine2D Integration
This is the Spine2D integration for Visual Novel Machinery.

If you intend to use this in your project you need to have your own [Spine license](https://esotericsoftware.com/spine-purchase). **DO NOT USE THIS WITHOUT THE LICENSE!**

## Setup
1. Follow the instructions [here](https://github.com/EsotericSoftware/spine-runtimes/blob/4.1/spine-ue4/README.md#usage) to install the Spine Plugin into your project.
2. Add a folder in your Plugins folder called VisualNovelMachinerySpine2D.
3. Copy the contents of this repository into the folder you just created.
4. Start your Unreal Engine Project. On Start Up it will ask you to build the new plugins. Do so.

## Usage
1. Open the CharacterDisplayWidget blueprint
2. Click on File -> Reparent Blueprint.
3. Reparent the widget blueprint to BaseSpine2DCharacterDisplayWidget.
4. Add a Spine Widget right next the Character Image and call it "SpineCharacterImage"
5. Align the SpineCharacterImage in the same way as Character Image
6. Import your Spine Characters
7. Create a Data Table of type "VNM Spine 2D Character Definition"
8. Go to Project Settings -> Plugins -> Visual Novel Machinery Spine 2D and set the data table in the settings
9. Add your imported characters to it
10. Add your characters to the character definitions data table
11. Add all animations as emotions to the characters (Just keep the Image Definition empty)
11. You are good to go!