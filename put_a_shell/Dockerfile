FROM ubuntu@sha256:e9569c25505f33ff72e88b2990887c9dcf230f23259da296eb814fc2b41af999 AS app


WORKDIR /app
RUN useradd -m ctf
COPY main .
COPY ynetd .
COPY hook.sh .
COPY ./flag.txt .
RUN chmod +x main hook.sh ynetd
CMD /app/hook.sh