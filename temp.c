void *runThread(void *pao)
{
    pActiveObject temp = (pActiveObject)pao;
    void *data;
    int result;
    int done = 0;

    for (int i = 0; i < N; i++)
    {
        if (temp->func != AO_1){
            lockQueue(temp->queue);
            while (temp->queue->first == NULL) {
                pthread_cond_wait(&temp->queue->cond, &temp->queue->lock);
            }
            data = dequeueFromQueue(temp->queue);
            unlockQueue(temp->queue);
        }
        
        if (temp->func != NULL)
        {
            result = temp->func(data);
            if (temp->next)
            {
                lockQueue(temp->next->queue);
                enqueueToQueue(temp->next->queue, (void *)result);
                unlockQueue(temp->next->queue);
                signalQueueNotEmpty(temp->next->queue);
            }
        }
    }
    N = 0;
    return NULL;
}