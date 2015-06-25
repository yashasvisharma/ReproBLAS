TARGETS := libindexed.a
SUBDIRS :=

INSTALL_LIB := $(TARGETS)

LIBINDEXED := $(OBJPATH)/libindexed.a

libindexed.a_DEPS = cciconv_sub.o \
                    ccmconv_sub.o \
                    cialloc.o \
                    cicadd.o \
                    cicconv.o \
                    cicdeposit.o \
                    ciciadd.o \
                    ciciaddv.o \
                    ciciset.o \
                    cicupdate.o \
                    cinegate.o \
                    cinum.o \
                    ciprint.o \
                    cirenorm.o \
                    cisetzero.o \
                    cisiset.o \
                    cisize.o \
                    cisupdate.o \
                    cmcadd.o \
                    cmcconv.o \
                    cmcdeposit.o \
                    cmcmadd.o \
                    cmcmset.o \
                    cmcupdate.o \
                    cmdenorm.o \
                    cmnegate.o \
                    cmprint.o \
                    cmrenorm.o \
                    cmsetzero.o \
                    cmsmset.o \
                    cmsrescale.o \
                    cmsupdate.o \
                    ddiconv.o \
                    ddmconv.o \
                    dialloc.o \
                    dibound.o \
                    didadd.o \
                    didconv.o \
                    diddeposit.o \
                    didiadd.o \
                    didiaddv.o \
                    didiset.o \
                    didupdate.o \
                    dindex.o \
                    dinegate.o \
                    dinum.o \
                    diprint.o \
                    direnorm.o \
                    disetzero.o \
                    disize.o \
                    dmbins.o \
                    dmdadd.o \
                    dmdconv.o \
                    dmddeposit.o \
                    dmdenorm.o \
                    dmdmadd.o \
                    dmdmaddsq.o \
                    dmdmset.o \
                    dmdrescale.o \
                    dmdupdate.o \
                    dmindex.o \
                    dmindex0.o \
                    dmnegate.o \
                    dmprint.o \
                    dmrenorm.o \
                    dmsetzero.o \
                    dscale.o \
                    sialloc.o \
                    sibound.o \
                    sindex.o \
                    sinegate.o \
                    sinum.o \
                    siprint.o \
                    sirenorm.o \
                    sisadd.o \
                    sisconv.o \
                    sisdeposit.o \
                    sisetzero.o \
                    sisiadd.o \
                    sisiaddv.o \
                    sisiset.o \
                    sisize.o \
                    sisupdate.o \
                    smbins.o \
                    smdenorm.o \
                    smindex.o \
                    smindex0.o \
                    smnegate.o \
                    smprint.o \
                    smrenorm.o \
                    smsadd.o \
                    smsconv.o \
                    smsdeposit.o \
                    smsetzero.o \
                    smsmadd.o \
                    smsmaddsq.o \
                    smsmset.o \
                    smsrescale.o \
                    smsupdate.o \
                    sscale.o \
                    ssiconv.o \
                    ssmconv.o \
                    ufp.o \
                    ufpf.o \
                    zialloc.o \
                    zidiset.o \
                    zidupdate.o \
                    zinegate.o \
                    zinum.o \
                    ziprint.o \
                    zirenorm.o \
                    zisetzero.o \
                    zisize.o \
                    zizadd.o \
                    zizconv.o \
                    zizdeposit.o \
                    ziziadd.o \
                    ziziaddv.o \
                    ziziset.o \
                    zizupdate.o \
                    zmdenorm.o \
                    zmdmset.o \
                    zmdrescale.o \
                    zmdupdate.o \
                    zmnegate.o \
                    zmprint.o \
                    zmrenorm.o \
                    zmsetzero.o \
                    zmzadd.o \
                    zmzconv.o \
                    zmzdeposit.o \
                    zmzmadd.o \
                    zmzmset.o \
                    zmzupdate.o \
                    zziconv_sub.o \
                    zzmconv_sub.o \
