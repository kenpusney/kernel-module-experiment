#!/usr/bin/env python
# -*- coding: utf-8 -*-

import urllib2

gh_url = 'https://api.github.com'

req = urllib2.Request(gh_url)

handler = urllib2.urlopen(req)

print handler.getcode()
print handler.headers.getheader('content-type')