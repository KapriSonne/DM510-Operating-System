/*
 * cycledetection.h
 *
 *  Created on: Nov 25, 2016
 *      Author: jacob
 */
#ifndef CYCLEDETECTION_H_
#define CYCLEDETECTION_H_


/*
 * Runs Kahn's algorithm on the graph, and outputs 'CYCLE DETECTED!\n'
 * if a DAG cannot be created, or the vertices as a list fx. '4, 0, 1, 3, 2\n'
 * representing an ordering in the DAG.
 * The output is printed to stdout.
 */
void cycle_detection(graph *g);


#endif /* CYCLEDETECTION_H_ */
