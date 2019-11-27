#pragma once

int mbox_init(uint id);
int mbox_send(uint id, void *msg);
int mbox_recv(uint id, void *msg);
int mbox_try_send(uint id, void *msg);
int mbox_try_recv(uint id, void *msg);
