# miniRT – A Simple Ray Tracer

## 🧠 Project Overview

miniRT is a ray tracing engine developed in C as part of the 42 school curriculum. The project aims to simulate the behavior of light in a 3D environment to render photorealistic images. It serves as an introduction to computer graphics and ray tracing concepts.

## ⚙️ Features

- **Geometric Primitives**: Support for spheres, planes, and cylinders.
- **Lighting Model**: Implements ambient, diffuse, and specular lighting using the Phong reflection model.
- **Shadow Casting**: Calculates shadows to add realism to scenes.
- **Scene Description Parsing**: Reads scene configurations from `.rt` files, including camera setup, light sources, and objects.
- **Image Output**: Renders images and saves them in the PPM (Portable Pixmap) format.
- **Basic Camera Controls**: Supports field of view and camera positioning.

---

## 🛠️ Technologies Used

- C programming language  
- Math libraries for vector and matrix operations  
- File I/O for scene parsing  
- Algorithms for ray-object intersection and shading  
## 🛠️ Installation

Clone the repository:

```bash
git clone https://github.com/alphbarry/miniRT.git
cd miniRT
```

Compile the project:
```bash
make
```

🚀 Usage
```bash
Run the ray tracer with a scene file:
./miniRT scenes/scene.rt
🖼️ Example Scene
```

📄 License
This project is licensed under the MIT License - see the LICENSE file for details.

👨‍💻 Author
alphbarry – GitHub Profile
