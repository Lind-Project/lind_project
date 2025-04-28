# Use Ubuntu as the base image.
FROM ubuntu:latest

ENV DEBIAN_FRONTEND=noninteractive

# Install build-essential tools, git, libpq-dev, and wget.
RUN apt-get update && apt-get install -y \
    build-essential \
    git \
    libpq-dev \
    libssl-dev \
    postgresql-client \
    libcurl4-openssl-dev \
    libz-dev \
    libssl-dev \
    libuv1-dev \
    libjemalloc-dev \
    libsqlite3-dev \
    cmake \
    wget \
    && rm -rf /var/lib/apt/lists/*

# Create a directory for your application.
WORKDIR /app

# Copy your C source file into the container.
COPY . .

# (Optional) Copy a Makefile if you choose to use it.
# COPY Makefile .

# Compile your server code linking against facil.io and libpq.
RUN make build

EXPOSE 3000

CMD ["./tmp/fioapp"]
