# cg-yon
## Assignment 四 (4) - Animation

`GLFW_KEY_LEFT [+ None/4/5]` 			( Camera / Humanoid / Non-Humanoid ) ROTATE  
`GLFW_KEY_RIGHT [+ None/4/5]` 			( Camera / Humanoid / Non-Humanoid ) ROTATE  
`GLFW_KEY_UP [+ None/4/5]`	 			( Camera / Humanoid / Non-Humanoid ) ROTATE  
`GLFW_KEY_DOWN [+ None/4/5]` 			( Camera / Humanoid / Non-Humanoid ) ROTATE  
`GLFW_KEY_PAGE_UP [+ None/4/5]` 		( Camera / Humanoid / Non-Humanoid ) ROTATE  
`GLFW_KEY_PAGE_DOWN [+ None/4/5]` 		( Camera / Humanoid / Non-Humanoid ) ROTATE  
`GLFW_KEY_W [+ None/4/5]` 				( Camera / Humanoid / Non-Humanoid ) Move  
`GLFW_KEY_A [+ None/4/5]` 				( Camera / Humanoid / Non-Humanoid ) Move  
`GLFW_KEY_S [+ None/4/5]` 				( Camera / Humanoid / Non-Humanoid ) Move  
`GLFW_KEY_D [+ None/4/5]` 				( Camera / Humanoid / Non-Humanoid ) Move  
`GLFW_KEY_Z [+ None/4/5]` 				( Camera / Humanoid / Non-Humanoid ) Move  
`GLFW_KEY_X [+ None/4/5]` 				( Camera / Humanoid / Non-Humanoid ) Move  

`GLFW_KEY_1` Light 1 toggle  
`GLFW_KEY_2` Light 2 toggle  
`GLFW_KEY_3` Light 3 toggle  

Camera on a bezier curve  
`/` Toggle attach and release camera to the bezier curve  
`,/.` Increment/Decrement t value  
`;` Add Control Point
`; + SHIFT` Clear Control Points
`; + CTRL` Load points from file 'bezier'

`GLFW_KEY_H + 7/8/9 (dof) [+ SHIFT]` Humanoid LEFT_LEG_ANGLE  
`GLFW_KEY_J + 7/8/9 (dof) [+ SHIFT]` Humanoid RIGHT_LEG_ANGLE  
`GLFW_KEY_K + 7/8/9 (dof) [+ SHIFT]` Humanoid LEFT_ARM_ANGLE  
`GLFW_KEY_L + 7/8/9 (dof) [+ SHIFT]` Humanoid RIGHT_ARM_ANGLE  
`GLFW_KEY_U (+ SHIFT)` Humanoid LEFT_ELBOW_ANGLE  
`GLFW_KEY_I (+ SHIFT)` Humanoid RIGHT_ELBOW_ANGLE  
`GLFW_KEY_O (+ SHIFT)` Humanoid LEFT_KNEE_ANGLE  
`GLFW_KEY_P (+ SHIFT)` Humanoid RIGHT_KNEE_ANGLE  
`GLFW_KEY_T (+ SHIFT)` Humanoid TORSO_ANGLE  
`GLFW_KEY_Y (+ SHIFT)` Humanoid FACE_ANGLE  
`GLFW_KEY_MINUS` Humaniod expression cycle  

`GLFW_KEY_F (+ SHIFT)` Non humanoid headphones HEADBAND_ANGLE  
`GLFW_KEY_E (+ SHIFT)` Non humanoid headphones LEFT_HOUSING_ANGLE  
`GLFW_KEY_R (+ SHIFT)` Non humanoid headphones LEFT_HOUSING_ANGLE  
`GLFW_KEY_G (+ SHIFT)` Non humanoid headphones RIGHT_HOUSING_ANGLE  
`GLFW_KEY_V (+ SHIFT)` Non humanoid headphones RIGHT_HOUSING_ANGLE  

`C` Capture frame in a text file 'frames.txt'  
`C + SHIFT` Set the frame jump value  
`M` Load the frames from file 'frames.txt' into a buffer  
`N / B` Play the buffer one frame at a time next/prev  

`=` Play the frames at 60 FPS  
`= + SHIFT` Save each frame in a folder 'frames/'  
