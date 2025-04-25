# Use an official base image with Python and Conda pre-installed
FROM mambaorg/micromamba:1.4.2

# Set environment variables
ENV DEBIAN_FRONTEND=noninteractive
ENV MAMBA_DOCKERFILE_ACTIVATE=1

# Create a working directory
WORKDIR /workspace

# Install Jupyter Notebook and xeus-cling
RUN micromamba install -y -n base -c conda-forge \
    jupyterlab \
    notebook \
    xeus-cling \
    && micromamba clean --all --yes

# Expose the Jupyter Notebook default port
EXPOSE 8888

# Set the default command to start Jupyter Notebook
CMD ["jupyter", "notebook", "--ip=0.0.0.0", "--port=8888", "--no-browser", "--allow-root"]


