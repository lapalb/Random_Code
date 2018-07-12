#include "filter_list.h"

/* Include or exclude pmanlog from here */

const char *filter_list[] = {
               "[asic_",
               "[ether-if-module]",
               "[cman_fp]",
               "[fman]",
               "pmanlog",
               "tdllib",
               "services",
               "dbal",
               "cmdparser",
               "btrace",
               "(ERR): property open:",
               "buginf",

               "plogd",
               "[env]",
               "[envlib]",
               "[syshw]",
               "[cyan]",
               "[flash]",
               "[dbm]",
               "[smand]",
               "[parser]",
               "[bipc]",
               "[om]",
               "[aom]",
               "[devobj]",
               "[pm]",
               "[pmvec]",
               "[pm_vec]",
               "[qos]",
               "[ifm_main]",
               "[pm_tdl]",
               "[smc]",
               "[peer]",
               "[vista]",
               "[tdldbpersist]",
               "[tdl_greencore]",
               "[green-fe]",
               "[bcrdu]",
               "[uipeer]",
               "[cmlib_util]",
               "[interfaces]",
               "[ipc-shim]",
               "[tm_lib]",
               "[pm_pvlan]",
               "[dhcpsn]",
               "[source]",
               "[l2cp]",
               "[cce]",
               "[stats]",
               "[ipsg]",
               "[l3_intf]",
               "[sgacl]",
               "[rep]",
               "[sisf]",
               "[cef]",
               "[pbr]",
               "[ipc]",
               "[storm]",
               "syshw read device: ",
               ": bit map update pg = ",
               ": lcportmap active = ",
               ": active bitmap port ",
               "abcdefghijk",
               "Compare objs(Port manager Cfg):",
               "matm",
               "FP Auto Infra: lookup obj",
               "Error while calling dev_port_command ",
               "vstring@VS",
               "vrf_tbl_id_downstream@U32:0",
               "Function not implemented",
               "Nothing to convert",
               "(note): Active = 0 ",
               "dlopen SUCCEED for libdev_ephy_mrv",
               "IOMD_ETHER_IF: StarfleetSpaEtherHwidbInit: speed state",
               "SVL link is not up will start TUNING",
               "SVL link is up no tuning",
               "OBJ CONFIG NOTICE serdes set addr",
               "Successfully sent chasfs set message for obj",
               "(info): did not get board id",
               "Last Pkt from NifMgr  =",
               "Last Pkt from StkMgr  =",
               "IOMD_ETHER_IF: Initializing hwidb",
               "(debug): toc ",
               "jumboSize 2000 l2_mtu",
               "(info): got board id",
               "is part of",
               "is not supported",
               "CYAN feature ",
               "Bad part number ",
               "Unknown part number "
               "{smand_",

               (char *) 0 /* Don't edit this or add beyond this */
};

const char *include_filter_list[] = {
    "0.1 ID:0 Changed:[switch-1]",
    "SYS-5-RESTART: System restarted --",
    "SSH-5-ENABLED: SSH 1.99 has been enabled",
    "CRYPTO_ENGINE-5-KEY_ADDITION: A key named TP-self-signed-3661210606.server has been generated or imported",
    "SYS-6-BOOTTIME: Time taken to reboot after reload =  678 seconds",
    "PKI-2-NON_AUTHORITATIVE_CLOCK: PKI functions can not be initialized until an authoritative time source, like NTP, can be obtained.",
    "PLATFORM-6-RF_PROG_SUCCESS: RF state STANDBY HOT",
    "Active Switch bulk sync done",
    "Added a new ipc connection",
    "Audit power: cman main pfu starfleet init:0",
    "Audit power: feature enabled",
    "Audit power: Initialized redun operating mode none in chasfs",
    "Audit power: polling timer initialization done.",
    "Calling cman_starfleet_init_asic_desc",
    "CC 1 card type is d8b, 3467",
    "CC:false CLOSE_WRITE-CLOSE /tmp/rp/chasfs/cc/1/0/ state",
    "chasfs event: pman, opcode 1, entry_type 0, objname pman, name sw-nginx-service",
    "chasfs event: RP bay 0, opcode 1, entry_type 0, objname rp/0/0, name hostinfo",
    "chasfs event: RP bay 0, opcode 1, entry_type 1, objname rp/0/0, name ios_config_dirty",
    "chasfs event: RP bay 0, opcode 1, entry_type 1, objname rp/0/0, name rfrole",
    "chasfs event: RP bay 0, opcode 3, entry_type 1, objname rp/0/0, name rfrole",
    "Chasfs: mastership property active-fp set to fp/0/0",
    "Chasfs: mastership property standby-fp set to fp/1/0",
    "CHASFS: Send local midplane/idprom/pkt_ready setting to remote",
    "CHASFS: Set Mastership standby-rp-state sso-ready in fp",
    "CHASFS: Stack chassis 1 chasfs property valid",
    "CHASFS: Stack chassis 2 chasfs property valid",
    "CHASFS: Standby IOSd has become SSO ready",
    "Chasfs: started watch on hwprg/cc/0. Status Success",
    "chassis_type:44",
    "Check and Fix Egress Q Success for lpn 5 aal_rc 0",
    "Checking if licensing is supported and required",
    "CMLIB IPC Create Client: IOS",
    "CMLIB IPC: Successfully connected to iosd_cmrp TDL domain",
    "CMLIB RIPC channel terminated: ngmod-iosd-cman",
    "Constructing domain iosd_cmrp.rp_0_0_rp_0_0",
    "Could not get SPA 1/0 max power, error 5",
    "CPLD compat:  R0 ver  fru[0] chas[44]",
    "CPLD sfchassis: get vector starfleet",
    "CPLD sfehsa: setting master rp slot to 0",
    "CPLD SFEHSA state set: Active, rtn 0",
    "CPLD sfehsa state set: configuring local i2c",
    "CPLD sfehsa state set: unmasking interrupts",
    "DAD Obj: stack_mgr/distr_stack/dad not present.So not watching",
    "Declaring stack link:0 as down",
    "Declaring stack link:1 as no cable",
    "DISTR_STACK sv_init: init(0)",
    "DISTR_STACK sv_init: post-init(1)",
    "dsvl Obj: stack_mgr/distr_stack/pagp_dad",
    "Dual active detection links are not configured",
    "Dual IOS flags: 0",
    "Empty lc portmap file",
    "emshim-emclient RIPC connection pending",
    "Entity IPC connect done, Invalid fd",
    "Fan-tray init is successful for slot 2",
    "FED is ready, Starting up NIF Manager",
    "FED_PM-3-HW_ERROR: Chassis 2 R0/0: fed: Port Manager error -port set jumbo: hardware update failed.",
    "Found hwprg/rp/0/cpld_ver during troll value []",
    "Found hwprg/rp/0/slave_state during troll value [bootup]",
    "Found hwprg/rp/0/slave_state during troll value [tdb]",
    "FP 0 card type is 0, 0",
    "FP0 online: oir response w/ reload_immediate 0 sent successfully",
    "FP master init: F0 is active",
    "FP online: slot 0",
    "FP slot 0 setting pkt_ready = 0",
    "HA_CONFIG_SYNC-6-BULK_CFGSYNC_SUCCEED: Bulk Sync succeeded",
    "Handling port lpn 11 CONNECTION change from new status 4 old Status 1",
    "Handling port lpn 11 LINK change from new 1 old Status 0",
    "Handling port lpn 11 LINK change from new 1 old Status 1",
    "Handling port lpn 5 LINK change from new 1 old Status 0",
    "Handling port lpn 5 LINK change from new 1 old Status 1",
    "HW PFU Starfleet, reconfig num_fans from 1, to 1",
    "Informing Stack Mgr that stack link:1 has no cable present",
    "INITIAL SYNC DONE - First Full Sync to chassis: 2 @ 148",
    "IO FPGA Current CPLD version = 0x05, Firmware version = 0x05",
    "IO FPGA Skipping Upgrade",
    "IOS register message: init mqipc for slot 0 bay 0",
    "IOSXE-0-PLATFORM: Chassis 1 R0/0: udev: disk0: has been inserted",
    "IOSXE_OIR-6-INSCARD: Card (cc) inserted in slot 1",
    "IOSXE_OIR-6-INSCARD: Card (fp) inserted in slot F0",
    "IOSXE_OIR-6-INSSPA: SPA inserted in subslot 3/0",
    "IOSXE_OIR-6-ONLINECARD: Card (cc) online in slot 1",
    "IOSXE_OIR-6-ONLINECARD: Card (fp) online in slot F0",
    "IOSXE_OIR-6-REMCARD: Card () removed from slot 1",
    "IOSXE_OIR-6-REMSPA: SPA removed from subslot 3/0, interfaces disabled",
    "IOSXE_REDUNDANCY-6-PEER: Active detected switch 2 as standby.",
    "LINEPROTO-5-UPDOWN: Line protocol on Interface FortyGigabitEthernet1/0/5, changed state to up",
    "LINEPROTO-5-UPDOWN: Line protocol on Interface LI-Null0, changed state to up",
    "LINK-3-UPDOWN: Interface EOBC10/1, changed state to up",
    "LINK-3-UPDOWN: Interface FortyGigabitEthernet1/0/5, changed state to up",
    "LINK-3-UPDOWN: Interface LIIN10/2, changed state to up",
    "LINK-3-UPDOWN: Interface Lsmpi10/3, changed state to up",
    "LINK-5-CHANGED: Interface GigabitEthernet0/0, changed state to administratively down",
    "LINK-5-CHANGED: Interface Vlan1, changed state to administratively down",
    "Link change, but status 1 for lpn 11 not cleaned up",
    "Link change, but status 1 for lpn 5 not cleaned up",
    "Links are down for all dual active ports",
    "MASTERSHIP: CLOSE_WRITE-CLOSE active-fp",
    "MASTERSHIP: CLOSE_WRITE-CLOSE active-fp-state",
    "MASTERSHIP: CLOSE_WRITE-CLOSE global-active-rp",
    "MASTERSHIP: CLOSE_WRITE-CLOSE global-standby-rp",
    "MASTERSHIP: CLOSE_WRITE-CLOSE plat_act_swover_st",
    "MASTERSHIP: CLOSE_WRITE-CLOSE standby-fp",
    "MASTERSHIP: CLOSE_WRITE-CLOSE standby-rp-ehsa-state",
    "MASTERSHIP: CLOSE_WRITE-CLOSE standby-rp-state",
    "Message is: message@pm_port_cfg: {",
    "Message received for rf role change ",
    "MQIPC finished processing initial messages.",
    "NGMOD_IPC: CMAN NGMOD IOSD IPC READY",
    "NGMOD_IPC: RIPC with IOSd returned a success code",
    "NIF: Init - Stack Platform Info Message Sent",
    "NIF_IPC: Connection Complete: 18",
    "NIF: Link Status TDL LIPC Msg Send failed: Invalid argument",
    "NIF: Link Status TDL - Port: 0, state: DOWN",
    "NIF: Link Status TDL - Port: 0, state: UP",
    "NIF: Link Status TDL - Port: 1, state: DOWN",
    "NIF: LIPC Connect to Stack Mgr Successful",
    "NIF_MGR-6-PORT_CONNECTION_STATUS_CHANGE: Chassis 1 R0/0: nif_mgr: PORT lpn:11 changed state from Pending to Ready.",
    "NIF_MGR-6-PORT_CONN_PENDING: Chassis 1 R0/0: nif_mgr: Port 11 on front side stack link 0 connection is PENDING.",
    "NIF_MGR-6-PORT_CONN_READY: Chassis 1 R0/0: nif_mgr: Port 11 on front side stack link 0 connection is READY.",
    "NIF_MGR-6-PORT_CONN_TIMEOUT: Chassis 1 R0/0: nif_mgr: Port 11 on front side stack link 0 connection has TIMEOUT: CONN_ERR_CONN_TIMEOUT_ERR",
    "NIF_MGR-6-PORT_LINK_UP: Chassis 1 R0/0: nif_mgr: Port 5 on front side stack link 0 is UP.",
    "NIF_MGR-6-STACK_LINK_UP: Chassis 1 R0/0: nif_mgr: Front side stack link 0 is UP.",
    "NIF_MGR: Send Bipc msg to Stk Mgr BIPC Handle is NULL",
    "NIF_MGR: Starting NIf Mgr stacking IPC ",
    "NIF: rtu_support_in_stack_mgr 0",
    "Not setting domain for cman_fp",
    "Not setting domain for cmcc",
    "Object fed_sdp has been created!",
    "Object fss_lnk_status has been created!",
    "Object lmp_fed_to_nif_mgr has been created!",
    "Object lmp_nif_mgr_to_fed has been created!",
    "Object nif_mgr_to_fed_iosd_msg has been created!",
    "Object nif_mgr_to_fed_port_bundle has been created!",
    "Object shut_nif has been created!",
    "Object stack_mgr/distr_stack/vsl/vsl2 is not present, continuing",
    "Obj: stack_mgr/distr_stack/vsl/vsl1",
    "ONEP_BASE-6-SS_ENABLED: ONEP: Service set Base was enabled by Default",
    "Peer attached: fru cc1:-1, ipc_channel 0x5638df0ffbe0",
    "Peer attached: fru rp0:0, ipc_channel 0x555e99aa3c30",
    "Periodic BACKUP sync of non-inotify dirs",
    "PMAN-3-PROC_EMPTY_EXEC_FILE: Chassis 2 R0/0: pvp: Empty executable used for process ngiolite",
    "PNP-6-PNP_DISCOVERY_STOPPED: PnP Discovery stopped (Startup Config Present)",
    "portmap removal handling",
    "Rcvd. chasfs resend message",
    "Reallocating resource for ios_get_tp_info_response_params",
    "Reallocating resource for keybuff",
    "Reallocating resource for raw_msg",
    "Reallocating resource for tdl_cce_class",
    "Received IOSd Notify RF Role message (standalone IOS): role 1, mode 1",
    "Received IOSd Notify RF Role message (standalone IOS): role 1, mode 4",
    "Received message: message@client_reg: {",
    "Received message: message@iosd_notify_rf_role: {",
    "Received SSD FRU oir insert event",
    "Received standby IOSd state 0",
    "Receive SPA Response from IOS, action 1, slot 1, bay 0, result 0, rc 0",
    "Recovering timed out connection new status 1 old status 4 to NIF_MGR_CONN_PENDING",
    "REDUNDANCY-3-PEER_MONITOR: PEER_FOUND event on standby",
    "REDUNDANCY-5-PEER_MONITOR_EVENT: Active detected a standby insertion (raw-event=PEER_FOUND(4))",
    "Redundancy mode: old mode 0, new mode 1",
    "Redundancy mode: old mode 4, new mode 4",
    "Resolved HW library chassis type: STARFLEET_PROMETHEUS",
    "Restart: restarting in a running system",
    "RF-5-RF_TERMINAL_STATE: Terminal state reached for (SSO)",
    "serdes lib init completed: FRU 0, slot 0.",
    "serdes lib init starts in STARFLEET_PROMETHEUS .....",
    "Serdes library initailization done for FRU 0 slot 0 in STARFLEET_PROMETHEUS",
    "Server indicated error 0x400 in SRP2",
    "Setting connection new status 4 old status 1 to PORT_CONN_TIMEOUT",
    "Setting link new status 1 old status 0 to PORT_LINK_UP",
    "Setup ESI after receive event inbox/rp/0/.last_push",
    "SF SSD FRU ACT2 Authentication",
    "Shutdown: no frus configured shutdown",
    "SIF FLASH READ: FIPS KEY Read Failed",
    "Skipping SSD ACT2 auth: size = 1 buf = 1",
    "SMART_LIC-2-PLATFORM_ERROR: Smart Licensing has encountered an internal software error. Contact TAC: The platform provided UDI list has invalid valu",
    "SMART_LIC-6-AGENT_READY: Smart Agent for Licensing is initialized",
    "SMART_LIC-6-HA_ROLE_CHANGED: Smart Agent HA role changed to Standby.",
    "SMN: sending stack stable  detection TDL",
    "SNMP-5-COLDSTART: SNMP agent on host switch-1 is undergoing a cold start",
    "SPA 1/0 card type is 0xd8b (3467)",
    "SPA_OIR-6-OFFLINECARD: SPA (C9500-32QC) offline in subslot 3/0",
    "SPA OIR Remove processing for slot 1, bay 0",
    "SPA online: 1/0, oir_cause 1",
    "SPA online: 1/0, oir_cause 2",
    "SSH-5-ENABLED: SSH 1.99 has been enabled",
    "STACK ACK Value: 12345",
    "Stack link 0 Port 0 for lpn 11",
    "Stack link 0 Port 2 for lpn 5",
    "Stack link 0 STACK_LINK_UP",
    "STACKMGR-6-ACTIVE_ELECTED: Chassis 1 R0/0: stack_mgr: Chassis 1 has been elected ACTIVE.",
    "STACKMGR-6-CHASSIS_ADDED: Chassis 1 R0/0: stack_mgr: Chassis 1 has been added to the stack.",
    "STACKMGR-6-STACK_LINK_CHANGE: Chassis 1 R0/0: stack_mgr: Stack port 1 on Chassis 1 is down",
    "STACKMGR-6-STANDBY_ELECTED: Chassis 1 R0/0: stack_mgr: Chassis 2 has been elected STANDBY.",
    "stack_mgr_ack called",
    "Standby switch is sso ready and notifying                                       to dependent app's",
    "Startup: all inventory received...",
    "Startup: chasfs process object created",
    "Startup: init master sm: active, state s_master_standalone/32",
    "Startup: init master sm: standby, state s_master_idle/128",
    "Startup: restart: chasfs reinit, fru cc/1 init sm state to s_cc_request/48",
    "Startup: restart: chasfs reinit fru: c-fru = cc/1",
    "Startup: restart: chasfs reinit fru: fp-fru = fp/0",
    "State change detected. Sending iosd message from NIF to FED",
    "Successfully sent chasfs prop resend message ",
    "Successfully set chassis_model property under 1/rp/chasfs/midplane with C9500-32QC          ",
    "Successfully set chassis_type property under 2/rp/chasfs/midplane with STARFLEET_PROMETHEUS",
    "Successfully set model_revision_number property under 2/rp/chasfs/midplane with V00",
    "Successfully set number property under 2/rp/chasfs/idprom/assembly with 47A7",
    "Successfully set pkt_ready property under 2/rp/chasfs/fp/0 with true",
    "Successfully set platform_fam_type property under 2/rp/chasfs/midplane with STARFLEET",
    "Successfully set revision property under 1/rp/chasfs/idprom/assembly with 1",
    "Successfully set revision property under 2/rp/chasfs/idprom/assembly with 2",
    "Successfully set serial_number property under 1/rp/chasfs/midplane with CAT2042L2Q7",
    "Successfully set sudi property under 1/rp/chasfs/midplane with ",
    "Switch2:chassis_serial_number",
    "Switch is already Active. Active transition from Stack Mgr is ignored",
    "Sync CC/SPA /tmp/chassis/local/rp/chasfs/cc/1/0/ w/o delete",
    "SYS-3-HARIKARI: Process pki_app top-level routine exited",
    "SYS-5-CONFIG_I: Configured from memory by console",
    "SYS-5-LOG_CONFIG_CHANGE: Buffer logging: level debugging, xml disabled, filtering disabled, size (1000000)",
    "SYS-5-RESTART: System restarted --",
    "SYS-6-BOOTTIME: Time taken to reboot after reload =  481 seconds",
    "/tmp/chassis/local/rp/chasfs/cc/1/0/ Sync to global-active-rp: OK",
    "/tmp/chassis/local/rp/chasfs/mastership/ Sync to global-active-rp: OK",
    "/tmp/chassis/local/rp/chasfs/rp/0/0/etc/ Sync to global-active-rp: OK",
    "/tmp/chassis/local/rp/chasfs/rp/0/0/hostinfo/ Sync to global-active-rp: OK",
    "/tmp/chassis/local/rp/chasfs/rp/0/0/ Sync to global-active-rp: OK",
    "/tmp/chassis/local/ Sync to global-active-rp: OK",
    "/tmp/chassis/local/ Sync to global-standby-rp: OK",
    "TRANSCEIVER-6-INSERTED: Chassis 1 R0/0: iomd: transceiver module inserted in FortyGigabitEthernet1/0/11",
    "TRANSCEIVER-6-INSERTED: Chassis 1 R0/0: iomd: transceiver module inserted in FortyGigabitEthernet1/0/3",
    "TRANSCEIVER-6-INSERTED: Chassis 2 R0/0: iomd: transceiver module inserted in FortyGigabitEthernet1/0/11",
    "UPDATED: global-active-rp chassis_num = 1",
    "UPDATED: global-standby-rp chassis_num = 2",
    "UPDATED: my chassis_num = 1",
    "Update the insert portmap xml",
    "Updating chasfs FRU cc1/-1 power consumption 500000 MW",
    "Updating chasfs FRU fp0/-1 power consumption 0 MW",
    "Uptime Timer (300s) started",
    "Waiting for FED to be ready",
    (char *) 0
};


/*-----------*/

int distance(const char * word1,int len1,const char * word2, int len2)
{
    //Find similarity between two string using Lavenstein  distance. Minimum number of insert,delete and s
    //replacement to convert source string to target string.
    int matrix[len1 + 1][len2 + 1];
    int i;

    for (i = 0; i <= len1; i++) {
        matrix[i][0] = i;
    }
    for (i = 0; i <= len2; i++) {
        matrix[0][i] = i;
    }

    for (i = 1; i <= len1; i++) {
        int j;
        char c1;

        c1 = word1[i-1];
        for (j = 1; j <= len2; j++) {
            char c2;

            c2 = word2[j-1];
            if (c1 == c2) {
                matrix[i][j] = matrix[i-1][j-1];
            }
            else {
                int delete;
                int insert;
                int substitute;
                int minimum;

                delete = matrix[i-1][j] + 1;
                insert = matrix[i][j-1] + 1;
                substitute = matrix[i-1][j-1] + 1;
                minimum = delete;
                if (insert < minimum) {
                    minimum = insert;
                }
                if (substitute < minimum) {
                    minimum = substitute;
                }
                matrix[i][j] = minimum;
            }
        }
    }
    return matrix[len1][len2];
}

/*-----------*/
