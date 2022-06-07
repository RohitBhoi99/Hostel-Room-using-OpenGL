# Hostel Room using OpenGL (C++)

We have rendered a hostel corridor having 8 identical furnished rooms in OpenGL.
The rooms have basic furniture like Beds, Tables, Almirahs, Doors, Windows, Ceiling Fan etc.

The objects are Interactive. On a button press, we can open and close the doors and windows, rotate the fan, etc.
Camera movement is also implemented.

The coordinates of these objects are hard-coded. 
The room also features lightning effect with 2 lights in each room.
Libraries used are GLEW and FreeGlut.

Preview Image:

![Mini-project preview image_2](https://user-images.githubusercontent.com/86927636/172346122-90ceeca2-3312-4600-979d-e699da6f1cb1.png | width=100px)


Requirements to run the file:

	Must have installed GL/glut.h and GL/freeglut.h

Keys for performing various actions in the project:

	1. Movement
		w: forward
		a: left
		s: back
		d: right

	2. Camera Rotation
		r: right
		f: left

	3. Fan Speed:
		x: increase
		z: decrease		

	4. Main Door Open and Close
		t: Open Door
		g: Close Door

	5. Almirah Doors
		y: Open Door
		h: Close Door

	6. Lights On/Off
		l: On/Off

	7. Window Open/Close
		o: Close
		p: Open

	8. Crouch/Stand up
		c: crouch down
		v: Stand Up

	To Move the cloth, increase fan speed by pressing ‘x’.
