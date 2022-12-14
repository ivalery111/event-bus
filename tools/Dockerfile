FROM debian:bullseye-slim

ARG DEBIAN_FRONTEND=noninteractive
ARG USERNAME=builder
ARG UID=1000
ARG GID=1000
ARG OH_MY_ZSH_COMMIT="d93f3174504f8a0c21aef6998714e3b67ba82606"

ENV SHELL="/bin/zsh"        \
    HOME="/home/${USERNAME}"

RUN apt-get update && apt-get install -y --no-install-recommends    \
    sudo                                                            \
    curl                                                            \
    ca-certificates                                                 \
    git                                                             \
    vim                                                             \
    cmake                                                           \
    build-essential                                                 \
    gcc                                                             \
    clang                                                           \
    zsh                                                             \
    zsh-autosuggestions                                             \
    zsh-syntax-highlighting                                         \
    bear                                                         && \
    apt-get clean

RUN useradd -m -s ${SHELL} ${USERNAME} && \
    adduser ${USERNAME} sudo && \
    echo "${USERNAME}:${USERNAME}" | chpasswd
RUN echo '%sudo ALL=(ALL) NOPASSWD:ALL' >> /etc/sudoers

WORKDIR ${HOME}

USER ${USERNAME}

# Setting OMZ
RUN sh -c "$(curl -fsSL https://raw.github.com/ohmyzsh/ohmyzsh/${OH_MY_ZSH_COMMIT}/tools/install.sh)"

CMD ["/bin/zsh"]
