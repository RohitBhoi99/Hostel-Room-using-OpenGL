# Hostel Room using OpenGL (C++)

We have rendered a hostel corridor having 8 identical furnished rooms in OpenGL.
The rooms have basic furniture like Beds, Tables, Almirahs, Doors, Windows, Ceiling Fan etc.

The objects are Interactive. On a button press, we can open and close the doors and windows, rotate the fan, etc.
Camera movement is also implemented.

The coordinates of these objects are hard-coded. 
The room also features lightning effect with 2 lights in each room.
Libraries used are Glut and FreeGlut.

Preview Image:


<img src="https://user-images.githubusercontent.com/86927636/172348193-2f3dd121-a655-479d-a139-a5eb1f64e84a.png" width="500" height="500">

Video Reference: https://drive.google.com/file/d/1eTPYZzYSHC33mDO_SHy28-bfEnOLFeVR/view?usp=sharing

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
