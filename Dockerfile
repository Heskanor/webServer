FROM debian:buster
COPY /script.sh /
RUN chmod 777 script.sh
CMD ["bash", "script.sh"]
