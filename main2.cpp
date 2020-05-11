void processInput()
{
    int M, N, S, C;
    int x, y;

    if (scanf("%d,%d", &M, &N) == 0)
        return;
    if (scanf("%d,%d", &S, &C) == 0)
        return;

    Graph graph(M * N);

    for (int i = 1; i < MN + 1; i++)
    {
        //right
        if (i % N != 0)
            graph.addEdge(i, i + 1, 1);

        //under
        if (i < M(N - 1))
            graph.addEdge(i, i + N, 1);
    }

    for (int i = 0; i < S; i++)
    {
        if (scanf("%d %d", &x, &y) == 0)
            return;

        graph.addEdge(M + 1, Nx + y + 1);
    }

    for (int i = 0; i < C; i++)
    {
        if (scanf("%d %d", &x, &y) == 0)
            return;

        graph.addEdge(0, Nx + y + 1);
    }
}