FROM ubuntu

COPY /src /app
WORKDIR /app
RUN apt update && apt install -y build-essential

CMD [ "make", "test" ]