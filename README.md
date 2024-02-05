## <h1 align="center">"Super Pang"</h1>
[![Watch the video](https://img.youtube.com/vi/St8FbgU1i8o/maxresdefault.jpg)](https://www.youtube.com/watch?v=St8FbgU1i8o)


## Overview:
The Super Pang Clone project is a commendable effort to recreate the iconic arcade game "Super Pang" using C++ and the SFML library. The project incorporates advanced programming techniques, data structures, design patterns, and physics mechanics to deliver a well-rounded gaming experience. Below is a detailed review of the project's key aspects.

## Technologies Used:
- **SFML** Simple and Fast Multimedia Library - for graphics and sounds.

## Project Structure - main classes:
- **Controller**: Responsible for the game loop handling and gameplay flow.
- **Menu**: Manage the user interface of the game.  
- **Level**: Load the levels from the file and holds the current game objects.
- **GameObj**: Virtual Base class for all the game objects.
- **CollisionHandling**: Responsible on all the collision process - detection and handling.
- **Animation**: Make the game animation such as walking etc.
- **ScoreBoard**: Manage the game score, load and save data in files.
- **Utilities**: Contains necessary data such as defines and enum classes.
- **Resources**: Singleton class that holds the game assets.
- **Sounds**: Singleton class for all the sounds effects. 

## Getting Started:
1. Clone the repository to your local machine.
   ```bash
   git clone <https://github.com/Daniel959595/Super-Pang.git>
2. Install SFML library: <a href="https://www.sfml-dev.org/download.php">Download from here</a>.
3. Extract the library and make sure its in the exact path as follow: "C:/SFML/SFML-2.5.1/lib/cmake/SFML".

## Programming Techniques:
In this project we used advanced programming techniques such as inheritance, polymorphism, templates, shared_ptr, exception handling and more. These techniques contribute to code reusability and maintainability, enhancing the project's overall quality. 

## Data Structures::
The project leverages standard template library (STL) data structures like vectors and shared_ptr, and maps, This choice enhances the efficiency of data manipulation. 

## Design Patterns::
The incorporation of design patterns, including reading data from files, basic virtual classes, and separate classes for every aspect of the game is a thoughtful and structured approach to promotes flexibility and extensibility.

## Collision Handling:
The adoption of the "multi methods" approach and collisionMap for collision handling is a notable design decision. This method enhances efficiency in managing collisions, providing a robust solution for the gameplay experience.

## Physics Mechanics:
The physics mechanics of this game were self implemented to provide the original game experience. 

## Licence:
Free for personal use, some of the assets of the game such as sprites and sound effects might be under copyright.
