FROM aflplusplus/aflplusplus

RUN apt update && apt install -y libglfw3-dev screen tmux

# Allow using the mouse in tmux
RUN { \
		echo "set -g mouse on"; \
	} > ~/.tmux.conf

# Allow using the mouse in screen
RUN { \
		echo "mousetrack on"; \
		echo "defmousetrack on"; \
	} > ~/.screenrc

COPY ./scripts/ /tmp/scripts
RUN chmod +x /tmp/scripts/*
RUN mv /tmp/scripts/* /usr/bin/

WORKDIR /src

# CMD [ "setup.sh" ]
