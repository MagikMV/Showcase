using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MoveThemBalls : MonoBehaviour
{
    public float speed = 0.001f;
    public GameObject homeBall, startBall, goalBall;
    private GameObject currentBall;
    private Vector3 w, s, a, d, e, q;

    void Start()
    {
        currentBall = homeBall;

        w = new Vector3(0, 0, speed);
        s = new Vector3(0, 0, -speed);
        a = new Vector3(-speed, 0, 0);
        d = new Vector3(speed, 0, 0);
        e = new Vector3(0, speed, 0);
        q = new Vector3(0, -speed, 0);
    }

    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Alpha1))
            currentBall = homeBall;
        else if (Input.GetKeyDown(KeyCode.Alpha2))
            currentBall = startBall;
        else if (Input.GetKeyDown(KeyCode.Alpha3))
            currentBall = goalBall;

        if (Input.GetKey(KeyCode.W))
            currentBall.transform.position += w;
        if (Input.GetKey(KeyCode.S))
            currentBall.transform.position += s;
        if (Input.GetKey(KeyCode.A))
            currentBall.transform.position += a;
        if (Input.GetKey(KeyCode.D))
            currentBall.transform.position += d;
        if (Input.GetKey(KeyCode.E))
            currentBall.transform.position += e;
        if (Input.GetKey(KeyCode.Q))
            currentBall.transform.position += q;
    }
}
