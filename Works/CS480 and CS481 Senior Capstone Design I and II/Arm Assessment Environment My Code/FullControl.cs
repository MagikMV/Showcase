using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FullControl : MonoBehaviour
{
    public GameObject target;
    private Vector3 w, s, a, d, e, q;
    private float speed = 0.3f;

    void Start()
    {
        w = new Vector3(0, 0, speed * Time.deltaTime);
        s = new Vector3(0, 0, -speed * Time.deltaTime);
        a = new Vector3(-speed * Time.deltaTime, 0, 0);
        d = new Vector3(speed * Time.deltaTime, 0, 0);
        e = new Vector3(0, speed * Time.deltaTime, 0);
        q = new Vector3(0, -speed * Time.deltaTime, 0);
    }

    public void ResetTarget()
    {
        target.transform.localPosition = new Vector3(0, 0, 0);
    }

    // Update is called once per frame
    void Update()
    {
        // if target is leaving the hand position, reset it
        if (Input.GetKey(KeyCode.W))
            target.transform.position += w;
        if (Input.GetKey(KeyCode.S))
            target.transform.position += s;
        if (Input.GetKey(KeyCode.A))
            target.transform.position += a;
        if (Input.GetKey(KeyCode.D))
            target.transform.position += d;
        if (Input.GetKey(KeyCode.E))
            target.transform.position += e;
        if (Input.GetKey(KeyCode.Q))
            target.transform.position += q;
    }
}
