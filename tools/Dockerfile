FROM alpine:3.17

ARG USERNAME=builder
ARG UID=1000
ARG GID=1000
ARG OH_MY_ZSH_COMMIT="d93f3174504f8a0c21aef6998714e3b67ba82606"

ENV SHELL="/bin/zsh"               \
    HOME="/home/${USERNAME}"    

RUN apk update --no-cache &&        \
    apk add --no-cache              \
    sudo                            \
    bash=5.2.12-r0                  \
    curl=7.86.0-r1                  \
    tzdata=2022f-r1

# Setting timezone
RUN cp /usr/share/zoneinfo/Europe/Moscow /etc/localtime && \
    echo "Europe/Brussels" > /etc/timezone

# Setting user
RUN adduser -s ${SHELL} -D ${USERNAME}                      && \
    echo "${USERNAME}:${USERNAME}" | chpasswd               && \
    adduser ${USERNAME} wheel                               && \
    echo '%wheel ALL=(ALL) NOPASSWD:ALL' >> /etc/sudoers
USER ${USERNAME}

WORKDIR ${HOME}

RUN sudo apk add --no-cache                         \
    git=2.38.2-r0                                   \
    python3=3.10.9-r1                               \
    py3-pip=22.3.1-r1                               \
    make=4.3-r1                                     \
    cmake=3.24.3-r0                                 \
    gcc=12.2.1_git20220924-r4                       \
    g++=12.2.1_git20220924-r4                       \
    clang=15.0.6-r0                                 \
    clang-extra-tools=15.0.6-r0                     \
    zsh=5.9-r0                                      \
    zsh-autosuggestions=0.7.0-r0                    \
    zsh-syntax-highlighting=0.7.1_git20220514-r0    \
    font-source-code-pro-nerd=2.1.0-r10             \
    ctags=5.9.20221002.0-r1                         \
    xclip=0.13-r3

# Setting ZSH
RUN sh -c "$(curl -fsSL https://raw.github.com/ohmyzsh/ohmyzsh/${OH_MY_ZSH_COMMIT}/tools/install.sh)"

CMD ["/bin/zsh"]
