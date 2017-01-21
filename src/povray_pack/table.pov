/*************************************************************************
** Pov-ray file
** This is a pretty simple homework which renders a scene with table and 
** walls, to practice POV-RAY.
*************************************************************************/

#include "shapes.inc"
#include "colors.inc"
#include "textures.inc"
#include "woods.inc"
#include "glass.inc"

/* Texture: Wood colormap */
#declare M_Wood18B =
colour_map {
    [0.00 0.25   color rgbf < 0.50, 0.26, 0.12, 0.10>
                 color rgbf < 0.54, 0.29, 0.13, 0.20>]
    [0.25 0.40   color rgbf < 0.54, 0.29, 0.13, 0.20>
                 color rgbf < 0.55, 0.28, 0.10, 0.70>]
    [0.40 0.50   color rgbf < 0.55, 0.28, 0.10, 0.70>
                 color rgbf < 0.50, 0.23, 0.15, 0.95>]
    [0.50 0.70   color rgbf < 0.50, 0.23, 0.15, 0.95>
                 color rgbf < 0.56, 0.29, 0.17, 0.70>]
    [0.70 0.98   color rgbf < 0.56, 0.29, 0.17, 0.70>
                 color rgbf < 0.54, 0.29, 0.13, 0.20>]
    [0.98 1.00   color rgbf < 0.54, 0.29, 0.13, 0.20>
                 color rgbf < 0.50, 0.26, 0.12, 0.10>]
}

/* Basic wood texture */
#declare Tex0 =
texture {
    pigment { P_WoodGrain12B color_map { M_Wood18B }}
}

/* The texture of table */
#declare TexTable = 
texture { Tex0
    finish {
        phong 1 phong_size 200
        ambient 0.25 diffuse 1
        specular 0.25 roughness 0.075
    }
    normal { bumps 0.75 } // Make some bumps!
}

/* The packages of table */
#declare TableTop = 
box { <-5.00, 0.0, -2.50>,
      < 5.00, -1.50, 2.50> }

#declare FrontLeftLeg =
cylinder { <-3.00, -1.50, -1.50>,
           <-3.00, -5.50, -1.50>, 0.75 }

#declare BackLeftLeg =
cylinder { <-3.00, -1.50,  1.50>,
           <-3.00, -5.50,  1.50>, 0.75 }

#declare BackRightLeg =
cylinder { < 3.00, -1.50,  1.50>,
           < 3.00, -5.50,  1.50>, 0.75 }

#declare FrontRightLeg =
cylinder { < 3.00, -1.50, -1.50>,
           < 3.00, -5.50, -1.50>, 0.75 }

/* Table Objects */
#declare Table = 
union {
    object { TableTop }
    object { FrontLeftLeg }
    object { BackLeftLeg }
    object { BackRightLeg }
    object { FrontRightLeg }
    texture { TexTable }
}

/* The texture of walls */
#declare WallTex = 
texture {
    pigment { color rgb<0.35, 0.32, 0.36> }
    finish { ambient 0.1 diffuse 1  reflection 0.10 }
}

/* The texture of ground */
#declare GroundTex = 
texture {
    pigment { color rgb <0.45, 0.52, 0.46> }
    finish { ambient 0.1 diffuse 1 }
    normal { bumps 0.4 } // Make some bumps
}

/* Wall planes */
#declare WallPlaneLeft = plane { <1, 0, 0>, -7.5 }
#declare WallPlaneBack = plane { <0, 0, 1>,  5.5 }
#declare Ground        = plane { <0, 1, 0>, -5.5 }

/* The environment - ground and walls */
#declare Env =
union {
    union { // Walls
        object{ WallPlaneLeft }
        object{ WallPlaneBack }
        texture { WallTex }
    }
    object {
        Ground
        texture { GroundTex }
    } // Ground
}    

/* The screen of laptop */
#declare Screen =
box { <-1.40, 0.10, -0.03>,
      < 1.40, 2.00,  0.03>   
    texture { // Black screen
    pigment { color rgb <0.01, 0.01, 0.01> }
        finish {
            phong 0.8 phong_size 200
            ambient 0.5 diffuse 1
        } 
    }
} 

/* The border of screen */
#declare ScreenBorder = 
object { // A simple super-torus
    Supertorus(1.00, 0.05, 0.01, 0.85, 0.001, 1.50)
    texture {
        pigment { color rgb <0.85, 0.66, 0.46> }
        finish {
            phong 0.8 phong_size 200
            ambient 0.2 diffuse 1
        } 
    }
    rotate <90, 0, 0>  
    scale <1.45, 1, 1>
    translate <0, 1.05, 0>
}

/* The basic texture setting of keyboard */
#declare KeyBoardTex =
texture {
    finish {
        phong 1.0 phong_size 200
        ambient 0.2 diffuse 1
    }
}

/* The border of keyboard */
#declare KeyBoardBorder =
box { <-1.50, 0.0, -1.55>,
      <1.50, 0.05, -0.05>   
    texture {
        KeyBoardTex
        pigment{ rgb<0.85, 0.66, 0.46> }
    }
}

/* The key press on the keyboard */
#declare KeyBoardPress =
box { <-1.30, 0.00, -1.35>,
      < 1.30, 0.06, -0.25>
    texture {
        KeyBoardTex 
        pigment { // Brick color texture 
            brick color rgb <1.00, 1.00, 1.00>
                  color rgb <0.05, 0.05, 0.05> 
            scale 0.03
        } 
    }
}

/* The keyboard of laptop */
#declare KeyBoard =
union {
    object { KeyBoardBorder }
    object { KeyBoardPress }
}

/* The laptop on the table */
#declare Laptop = 
union {
    union {
        object { Screen } // The screen
        object { ScreenBorder } // The border of screen
        rotate <20.00, 0, 0> // A little rotation
    }
    object { KeyBoard } // The keyboard
}

/* The mouse of laptop */
#declare Mouse =
sphere { <0, 0, 0>, 0.25
    scale <1.00, 0.90, 1.88>  
    pigment { color rgb <1.00, 1.00, 1.00> }
    texture { 
        pigment { // Brick color texture 
            brick color rgb <0.50, 0.50, 0.50>
                  color rgb <0.10, 0.10, 0.10> 
            scale 0.1
        }
    }
    finish{
        phong 0.8
        phong_size 200
    }
    translate <2.00, 0.00, -1.50>  
}

/* A glass ball */
#declare GlassBall =
sphere {
    <-2.80, 0.50, 0.00>, 0.5
    material {
        texture {
            pigment { color rgbf <0.98, 1.0, 0.99, 0.75> }
            finish { F_Glass4 }
        }
        interior {I_Glass caustics 1}
    }
}

/* The texture of blanket */
#declare BlanketTex =
pigment {
   gradient z
   color_map {
      [0.00, rgb <0.21, 0.42, 0.41>]
      [0.60, rgb <0.21, 0.42, 0.41>]
      [0.60, rgb <0.88, 0.98, 0.87>]
      [1.00, rgb <0.88, 0.98, 0.87>]
   }
   frequency 4
}

/* A simple blanket on the table */
#declare Blanket =
box {
    <-4.00, 0.00, -2.00>,
    <-2.00, 0.02,  2.00>
    texture {
        pigment {
            gradient x
            pigment_map {
                [0.0, BlanketTex]
                [0.5, BlanketTex]
            }
            warp {
                turbulence 0.05
                octaves 2
            }
        }
        normal {
            quilted 0.6
            scale 0.025
            warp {
                turbulence 0.05
                octaves 2
            }
        }
        scale <5.00, 5.00, 5.00>
        translate <10.00, 10.00, 10.00>
    }
}

/* Display scene */
union {
    object { Env }
    object { Table }
    object { Laptop }
    object { Mouse }
    object { GlassBall }
    object { Blanket }
}

/* Camera settings */      
camera {
    location <-3.5, 3.5, -10>
    look_at <0.0, 0.0, 0.0>
    angle 100.00
    right x * image_width / image_height
}

/* Light source settings */
light_source { <50.0, 100.0, -100.0> 
    color rgb <1.00, 1.00, 1.00>
}

/* Simple background */
background {
    color rgb <0.23, 0.45, 0.80>
}
 