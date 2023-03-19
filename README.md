# Note Number ReMapper By Velocity VTS Plugin (Beta)

[<img src="https://img.shields.io/badge/slack-@lesimoes/help-blue.svg?logo=slack">](https://lesimoes.slack.com/messages/C04JV5CRGJH) 
[<img src="https://img.shields.io/badge/discord-@lesimoes/help-blue.svg?logo=discord">](https://discord.gg/7xegRfQjPz) 

VTS plugin to remap a midi note number to another based on its velocity.

![screenshot](https://user-images.githubusercontent.com/5066378/226111440-5d9adbca-3bfd-4aa1-964a-64a4499571d7.png)

# Motivation

I started to create this plugin for a single purpose which is to workaround the problem with the Alesis Crimson 2 module that has only one single note for the HiHat, Crash Left and Crash Right, that's why in the BETA version you see these as groups, and also only three fixed possibilities of remapping, in this case, the notes 8 (HiHat), 49 (Crash Left), and 57 (Crash Right). Using this plugin together with your favorite drums VTS (Steven Slate, EZDrummer, etc) you can get it working better and have a sound more smooth and dynamic.

Now, I decided to turn this plugin into a more generic version by adding the possibility to remap more than just 3 fixed notes, so please if you like this plugin, consider supporting this project by opening issues, staring, or even donating.

### How to use this plugin?
I'm currently working on a video tutorial, but basically, you have to use this as a middleware from your midi device to the other midi plugins. 

#### Here is a quick step-by-step:

1. Select the input note to be remapped in the `Note IN` dropdown (bottom).
2. In the velocity slider (middle), select the velocity breakpoint that you want the note to be remapped. The note will be remapped after the velocity played passes this velocity breakpoint.
3. Select the output note in the Note OUT dropdown (top). This is the note that will be played after the note in remapping happens.

### Features

- [x] 22 remapping controls group.
- [x] 1 input note dropdown selector in each group.
- [x] 1 velocity breakpoint slider selector in each group.
- [x] 1 output note dropdown selector in each group.

#### In progress

- [ ] Change the off option in the dropdowns to an on/off toggle button.
- [ ] Add a "learn" button to the velocity slider so the user can set the velocity by playing instead of using the slider directly.
- [ ] Add a "learn" button to the `Note IN` dropdown so the user can set the note by playing instead of using the dropdown.
- [ ] Add notes keys in the notes dropdowns for a better UX.

### Credits

This project was created using [Juce Framework](https://juce.com/).

<img src="https://juce.com/wp-content/uploads/2022/07/JUCE-logo-horiz-ondark.png">
