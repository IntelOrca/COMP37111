Universty of Manchester  
COMP37111, Particle System  
Ted John, November 2013

# About
This was a particle system exercise for the Universty of Manchester, [Advanced Computer Graphics (COMP37111)](http://studentnet.cs.manchester.ac.uk/ugt/COMP37111). The application demonstrates five two dimensional scenarios using several changeable parameters to alter the appearance and physics. The particle system uses emitters with properties that control what, when and how many particles are emitted. All particles can be rendered using non-textured primitives (teapot, points, lines and circles) or textured quads from the texture directory. All textures are rendered using additive blending which gives better results than alpha blending.

The application is written in C and uses GLUT / OpenGL to render the scene and [lodepng](http://lodev.org/lodepng) to read the .png texture files. It took approximately 10 to 15 hours to write.

# Compiling
**Windows:**

Clone the repository and then open `./COMP37111.sln` in Visual Studio and build the project.

**Linux:**
```
git clone https://github.com/IntelOrca/COMP37111.git
cd COMP37111
./linuxcompileandrun
```

**Mac OS X:**
```
git clone https://github.com/IntelOrca/COMP37111.git
cd COMP37111
./maccompileandrun
```

# How to use
Use the up and down keys to navigate through the options in the menu (shown in the bottom left). Use the left and right keys to decrease or increase the option value. The last options is the demo, the following are available:

1. Fountain
2. Spiral
3. Snow
4. Fireworks
5. Triple fountain with collision
