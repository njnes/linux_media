#ifndef _STV0910_H_
#define _STV0910_H_

#include <linux/types.h>
#include <linux/i2c.h>

struct stv0910_cfg {
	u32 clk;
	u8  adr;
	u8  parallel;
	u8  rptlvl;
	u8  dual_tuner;
	
	/* Hook for Lock LED */
	void (*set_lock_led) (struct dvb_frontend *fe, int offon);

	void (*write_properties) (struct i2c_adapter *i2c,u8 reg, u32 buf); 
	void (*read_properties) (struct i2c_adapter *i2c,u8 reg, u32 *buf);	
};

#if IS_REACHABLE(CONFIG_DVB_STV0910)
extern struct dvb_frontend *stv0910_attach(struct i2c_adapter *i2c,
					   struct stv0910_cfg *cfg, int nr);
#else
static inline struct dvb_frontend *stv0910_attach(struct i2c_adapter *i2c,
						  struct stv0910_cfg *cfg,
						  int nr)
{
	pr_warn("%s: driver disabled by Kconfig\n", __func__);
	return NULL;
}

#endif

#endif
