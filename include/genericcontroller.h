/*
 * genericcontroller.h
 *
 *  Created on: 2014/5/15
 *      Author: sonicyang
 */

#ifndef GENERICCONTROLLER_H_
#define GENERICCONTROLLER_H_

class genericController {
public:
	genericController();
	virtual ~genericController();

	virtual int exec() = 0;

};

#endif /* GENERICCONTROLLER_H_ */
