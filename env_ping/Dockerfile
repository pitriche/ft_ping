FROM debian:bookworm-slim

# RUN apt update && apt install -y wget build-essential && \
#     wget http://ftp.gnu.org/gnu/inetutils/inetutils-2.0.tar.gz && \
#     tar xzf inetutils-2.0.tar.gz && cd inetutils-2.0 && \
#     ./configure && make && make install

RUN apt update
RUN apt install -y wget build-essential

RUN wget http://ftp.gnu.org/gnu/inetutils/inetutils-2.0.tar.gz
RUN tar xzf inetutils-2.0.tar.gz
RUN cd inetutils-2.0 && \
	./configure && \
	make && \
	make install

VOLUME /root/env
WORKDIR /root/env

CMD ["/bin/bash"]