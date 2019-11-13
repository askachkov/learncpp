TEMPLATE = subdirs

SUBDIRS += \
    sync \
    async \
    memberAsHandler \
    state_machine \
    thread_pool \
    serial_asio \
    boost_fusion \
    variant \
    web-client \
    time_server \
    time_client \
    c_server \
    serial_v2

DEPENDPATH += variant
