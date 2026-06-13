# 42_miniRT

*This project has been created as part of the 42 curriculum by brensant and rgomes-d*.

## Description

**miniRT** is a simple ray tracer written in C, developed as part of the 42 School curriculum. The goal of the project is to render a 3D scene described in a text file by simulating the behavior of light rays traveling from a virtual camera into the scene.

The renderer supports geometric primitives such as spheres, planes, and cylinders, along with transformations, multiple light sources, shadows, and the Phong reflection model. The bonus version also includes additional features such as object textures, checkerboard patterns, normal mapping, and other visual effects.

The project was built from scratch using only the allowed libraries and focuses on fundamental computer graphics concepts, including:

- Ray-object intersection algorithms
- Vector and matrix mathematics
- Coordinate space transformations
- Camera projection
- Lighting and shading models
- Shadow ray casting
- Texture mapping
- Surface normal manipulation

The objective of miniRT is not to compete with modern rendering engines, but to provide a practical understanding of the mathematical and computational principles behind ray tracing and image synthesis.

## Instructions

1. Clone the repository:

	```bash
	git clone --recurse-submodules https://github.com/Breno-S/42_miniRT.git
	```

2. Move into the project directory:

	```bash
	cd 42_miniRT
	```

3. Compile the project:

	```bash
	make bonus
	```

4. Run the executable passing a scene as an argument:

	```bash
	./miniRT ./scenes/scene1_bonus.rt
	```

# Resources

Here are some of the most useful resources used to understand and develop this project:

**General Computer Graphics and Ray Tracing Concepts**

- [Scratchapixel](https://www.scratchapixel.com/index.html)
- [How Ray Tracing Works - Computerphile - YouTube](https://www.youtube.com/watch?v=ezXGTRSx1g8)
- [Ray Tracing - MIT EECS 6.837](https://www.cs.tau.ac.il/~dcor/Graphics/adv-slides/ray-tracing16.pdf)

**Vector Math**

- [Essence of linear algebra - YouTube](https://youtube.com/playlist?list=PLZHQObOWTQDPD3MizzM2xVFitgF8hE_ab&si=N35MD8WjMQJEiYvS)
- [Rotation matrix - Wikipedia](https://en.wikipedia.org/wiki/Rotation_matrix)
- [Homogenous Transformation Matrices](https://www.cs.columbia.edu/~allen/F19/NOTES/homogeneous_matrices.pdf)

**Lighting**

- [Phong reflection model - Wikipedia](https://en.wikipedia.org/wiki/Phong_reflection_model)
- [Learn OpenGL - Basic Lighting](https://learnopengl.com/Lighting/Basic-Lighting)
- [9.2 Modelo de reflexão de Phong | MCTA008-17 Computação Gráfica](https://www.brunodorta.com.br/cg/phongmodel)

**Tutorials**

- [Ray tracing from scratch \[C++ & SDL2\]](https://youtube.com/playlist?list=PL3WoIG-PLjSt54LvzY2SuBQDl-cXa11Tm&si=wXBnVafVfaym2iIT)
- [Ray Tracing in One Weekend Series](https://raytracing.github.io/)
- [Desenvolvendo um Raytracer em C](https://youtu.be/2ojN-5kAw3s?si=NQJh61q2DOTWRYz8)

> [!IMPORTANT]
>
> During the development of this project, AI tools (such as ChatGPT) were used as a learning aid to clarify concepts related to ray tracing and help with some math equations. Also, this README was improved with AI. All architectural decisions, implementations, and debugging were performed by the authors, and no code was copied verbatim from AI-generated sources. The project was developed with the intent of understanding and applying the underlying concepts.
