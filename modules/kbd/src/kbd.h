#ifndef KBD_H
#define KBD_H


struct kbd_cfg {
	void (*print_cb)(const char*);
};


void kbd_init(const struct kbd_cfg *cfg);
void kbd_printkeys(const struct kbd_cfg *cfg);


#endif /* KBD_H */
