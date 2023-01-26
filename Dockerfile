FROM aflplusplus/aflplusplus

RUN apt update && apt install libglfw3-dev -y

COPY ./scripts/ /tmp/scripts
RUN chmod +x /tmp/scripts/*
RUN mv /tmp/scripts/* /usr/bin/

CMD [ "setup.sh" ]
