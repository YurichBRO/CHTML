from fastapi import FastAPI, Response
import subprocess
import sys


app = FastAPI()


def run_external_command(command):
    try:
        result = subprocess.run(
            command,
            capture_output=True,
            text=True,
            check=False  # We'll check manually
        )
        if result.returncode != 0:
             return f"""<html>
                        <head><title>Error</title></head>
                        <body><h1>Error</h1><p>Command failed with code: {result.returncode}. Error: {result.stderr}</p></body>
                    </html>"""

        return result.stdout

    except subprocess.CalledProcessError as e:
        return f"""<html>
                        <head><title>Error</title></head>
                        <body><h1>Error</h1><p>Command failed with error: {str(e)}. Error: {e.stderr}</p></body>
                    </html>"""
    except Exception as e:
        return f"""<html>
                        <head><title>Error</title></head>
                        <body><h1>Error</h1><p>Unexpected error: {str(e)}</p></body>
                    </html>"""


@app.get("/")
async def root():
    output = run_external_command(COMMAND)
    return Response(content=output, media_type="text/html")

if __name__ == "__main__":
    import uvicorn
    if len(sys.argv) < 2:
        print(f"Usage: python {sys.argv[0]} <command>")
        sys.exit(1)

    COMMAND = sys.argv[1:]
    uvicorn.run(app, host="localhost", port=8000)