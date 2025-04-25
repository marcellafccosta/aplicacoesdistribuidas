# puc_mda_openmp_mpi
Class Materials - Mobile and Distribuited Applications

This repository is dedicated to the studies about OpenMP and MPI. 

### Explanation of the Dockerfile
1. **Base Image**:
   - The `mambaorg/micromamba` image is used because it provides a lightweight Conda environment manager, which is ideal for installing `xeus-cling` and Jupyter.

2. **Install Dependencies**:
   - `jupyterlab` and `notebook`: For running Jupyter Notebook.
   - `xeus-cling`: The C++ kernel for Jupyter.

3. **Expose Port**:
   - Port `8888` is exposed to allow access to the Jupyter Notebook server.

4. **Default Command**:
   - The container starts a Jupyter Notebook server when run.

---

### Steps to Build and Run the Docker Image

1. **Save the Dockerfile**:
   Save the above content in a file named Dockerfile in your project directory.

2. **Build the Docker Image**:
   Run the following command to build the image:
   ```bash
   docker build -t jupyter-cpp-env .
   ```

3. **Run the Docker Container**:
   Start a container with the image:
   ```bash
   docker run -it --rm -p 8888:8888 -v $(pwd):/workspace jupyter-cpp-env
   ```

   - `-p 8888:8888`: Maps the container's Jupyter Notebook port to your local machine.
   - `-v $(pwd):/workspace`: Mounts the current directory into the container.

4. **Access Jupyter Notebook**:
   - Open your browser and go to `http://localhost:8888`.
   - Use the token provided in the terminal to log in.

---

### Test C++ in Jupyter Notebook
Once inside Jupyter Notebook:
1. Create a new notebook.
2. Select the **C++ (xeus-cling)** kernel.
3. Run a simple C++ program:
   ```cpp
   #include <iostream>
   std::cout << "Hello, World!" << std::endl;
   ```


