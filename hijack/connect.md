# Hijack connect() syscall

Code see `connect.c`.

GitHub IP:
```bash
root@ubuntu-xenial:/vagrant_data/kernel# dig api.github.com

; <<>> DiG 9.10.3-P4-Ubuntu <<>> api.github.com
;; global options: +cmd
;; Got answer:
;; ->>HEADER<<- opcode: QUERY, status: NOERROR, id: 32406
;; flags: qr rd ra; QUERY: 1, ANSWER: 2, AUTHORITY: 8, ADDITIONAL: 14

;; OPT PSEUDOSECTION:
; EDNS: version: 0, flags:; udp: 4096
;; QUESTION SECTION:
;api.github.com.			IN	A

;; ANSWER SECTION:
api.github.com.		566	IN	A	192.30.253.116
api.github.com.		566	IN	A	192.30.253.117
```

Kernel log:
```text
Jan 10 11:56:18 ubuntu-xenial kernel: [17827.616592] Connect to 74fd1ec0
Jan 10 11:56:18 ubuntu-xenial kernel: [17827.710041] Connect to 0
Jan 10 11:56:18 ubuntu-xenial kernel: [17827.776927] Connect to 75fd1ec0
Jan 10 11:56:18 ubuntu-xenial kernel: [17827.863909] Connect to 74fd1ec0
```