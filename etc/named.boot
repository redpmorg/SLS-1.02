;
;    boot file for name server
;
directory /usr/etc/inet

; type     domain                source host/file          backup file

;cache      .                                               root.cache
domain    softlanding.com
primary    softlanding.com          named.hosts
primary    0.0.127.IN-ADDR.ARPA                            named.local
primary    2.0.192.IN-ADDR.ARPA                         named.rev
;
;primary    Berkeley.EDU          berkeley.edu.zone
;primary    32.128.IN-ADDR.ARPA   ucbhosts.rev
;secondary  CC.Berkeley.EDU       128.32.137.8 128.32.137.3 cc.zone.bak
;secondary  6.32.128.IN-ADDR.ARPA 128.32.137.8 128.32.137.3 cc.rev.bak
;forwarders 10.0.0.78 10.2.0.78
; slave
