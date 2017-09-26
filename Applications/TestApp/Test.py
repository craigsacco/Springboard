#!/usr/bin/python

import serial
import struct

glbseqno = 1

def get_next_seqno():
    global glbseqno
    n = glbseqno
    glbseqno = glbseqno + 1
    if glbseqno == 256:
        glbseqno = 1
    return n

def send_message(iface, data):
    msg = struct.pack("<BBB", 0xfd, 0x02, len(data) + 1)
    msg += data
    msg += struct.pack("<BB", 0x03, 0xfc)
    checksum = 0
    for x in msg:
        checksum ^= ord(x)
    msg += struct.pack("<B", checksum)
    iface.write(serial.to_bytes(msg))

def get_message(iface):
    msg = iface.read(3)
    msg += iface.read((ord(msg[2]) - 1) + 3)
    sof, length = struct.unpack("<HB", msg[0:3])
    data = msg[3:(3+length)-1]
    eof, checksum = struct.unpack("<HB", msg[(3+length)-1:])
    expected = 0
    for x in msg[:-1]:
        expected ^= ord(x)
    if checksum != expected:
        raise Exception("checksum mismatch: {0} != {1}".format(checksum, expected))
    return data

def get_property(iface, resid, propid):
    seqno = get_next_seqno()
    msg = struct.pack("<BBHH", seqno, 0, resid, propid)
    send_message(iface, msg)
    rspdata = get_message(iface)
    rspseqno, rsptype, rspresid, rsppropid, resultcode = struct.unpack("<BBHHI", rspdata[0:10])
    if rsptype != 1:
        raise Exception("unexpected type: 1 != {0}".format(rsptype))
    if seqno != rspseqno:
        raise Exception("unexpected seqno: {0} != {1}".format(seqno, rspseqno))
    if resid != rspresid:
        raise Exception("unexpected resid: {0} != {1}".format(resid, rspresid))
    if propid != rsppropid:
        raise Exception("unexpected propid: {0} != {1}".format(propid, rsppropid))
    if resultcode != 0:
        raise Exception("get property request returned 0x{0:08x}".format(resultcode))
    return rspdata[10:]

def set_property(iface, resid, propid, propdata):
    seqno = get_next_seqno()
    msg = struct.pack("<BBHH", seqno, 2, resid, propid) + propdata
    send_message(iface, msg)
    rspdata = get_message(iface)
    rspseqno, rsptype, rspresid, rsppropid, resultcode = struct.unpack("<BBHHI", rspdata)
    if rsptype != 3:
        raise Exception("unexpected type: 3 != {0}".format(rsptype))
    if seqno != rspseqno:
        raise Exception("unexpected seqno: {0} != {1}".format(seqno, rspseqno))
    if resid != rspresid:
        raise Exception("unexpected resid: {0} != {1}".format(resid, rspresid))
    if propid != rsppropid:
        raise Exception("unexpected propid: {0} != {1}".format(propid, rsppropid))
    if resultcode != 0:
        raise Exception("set property request returned 0x{0:08x}".format(resultcode))

#url = "spy:///dev/ttyUSB0"
url = "/dev/ttyUSB0"
with serial.serial_for_url(url, timeout=1) as iface:
    iface.baudrate = 9600
    print "controller resource type: {0}".format(struct.unpack("<H", get_property(iface, 1, 1))[0])
    print "controller resource name: {0}".format(get_property(iface, 1, 2))
    print "controller RTOS type: {0}".format(get_property(iface, 1, 10))
    print "controller RTOS version: {0}".format(get_property(iface, 1, 11))
    print "expander resource type: {0}".format(struct.unpack("<H", get_property(iface, 2, 1))[0])
    print "expander resource name: {0}".format(get_property(iface, 2, 2))
    try:
        print "attempt to query invalid resource"
        get_property(iface, 0xdead, 1)
        assert False
    except Exception, ex:
        print ex
    try:
        print "attempt to query invalid property"
        get_property(iface, 1, 0xbeef)
        assert False
    except Exception, ex:
        print ex
    try:
        print "attempt to write to readonly property"
        set_property(iface, 1, 1, "www")
        assert False
    except Exception, ex:
        print ex

    while True:
        print struct.unpack("<H", get_property(iface, 2, 109))
