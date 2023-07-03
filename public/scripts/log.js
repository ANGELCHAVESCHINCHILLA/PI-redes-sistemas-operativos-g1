const PAGE_PRINCIPAL = "/index.html";

const reload_logs_btn = document.getElementById("reload-logs");
const logs_container = document.getElementById("logs-container");

const show_all_logs_btn = document.getElementById("show-all-logs");
const show_db_logs_btn = document.getElementById("show-db-logs");
const show_fs_logs_btn = document.getElementById("show-fs-logs");
const show_web_logs_btn = document.getElementById("show-web-logs");

const db_logs = document.getElementsByClassName("db-log-text");
const fs_logs = document.getElementsByClassName("fs-log-text");
const web_logs = document.getElementsByClassName("web-log-text");

const spinner = document.getElementById("spinner");

reload_logs_btn?.addEventListener("click", function (event) {
  reloadLogs();
})

function reloadLogs() {
  logs_container.innerHTML = "";
  spinner.style.display = "block";
  populateLogContainer();
}

show_all_logs_btn?.addEventListener("click", function (event) {
  const all_logs = [...db_logs, ...fs_logs, ...web_logs];
  Array.from(all_logs).forEach(elem => {
    elem.style.display = "block";
  })
})

show_db_logs_btn?.addEventListener("click", function (event) {
  Array.from(db_logs).forEach(elem => {
    elem.style.display = "block";
  })

  Array.from(fs_logs).forEach(elem => {
    elem.style.display = "none";
  })

  Array.from(web_logs).forEach(elem => {
    elem.style.display = "none";
  })
})

show_fs_logs_btn?.addEventListener("click", function (event) {
  Array.from(db_logs).forEach(elem => {
    elem.style.display = "none";
  })

  Array.from(fs_logs).forEach(elem => {
    elem.style.display = "block";
  })

  Array.from(web_logs).forEach(elem => {
    elem.style.display = "none";
  })
})

show_web_logs_btn?.addEventListener("click", function (event) {
  Array.from(db_logs).forEach(elem => {
    elem.style.display = "none";
  })

  Array.from(fs_logs).forEach(elem => {
    elem.style.display = "none";
  })

  Array.from(web_logs).forEach(elem => {
    elem.style.display = "block";
  })
})

/**
 * Populates the log_container element with logs
 */
async function populateLogContainer () {
  let logs = [];

  try {
    // get log file from web server
    await getLogsByServer("web", logs);
    // get log file from db server
    await getLogsByServer("db", logs);
    // get log file from fs server
    await getLogsByServer("fs", logs);
    // sort them
    logs.sort((a, b) => a.logTime - b.logTime);

    spinner.style.display = "none";
    // populate html
    logs.forEach((log) => {
      console.log(log);
      logs_container.insertAdjacentHTML("beforeend", log.htmlLog);
    })

  } catch (error) {
    alert("Could not retrieve logs: " + error);
  }
}

/**
 * 
 * @param {string} server the server whose log will be retrieved
 * @param {*} logs an array where the logs will be stored
 */
async function getLogsByServer(server, logs) {
  // get size of file
  const serverLogSizeResponse = await fetch(`/log/${server}/count`);
  const serverLogSize = await serverLogSizeResponse.text();
  console.log(serverLogSize);
  // get data
  const pageSize = 5;
  const pages = Math.ceil(+serverLogSize / pageSize);
  const module = +serverLogSize % pageSize;
  for (let i = 0; i < pages; ++i) {
    const logsResponse = await fetch(`/log/${server}/file?offset=${i * pageSize}&lines=${(i != pages - 1) ? pageSize : module}`);
    const logsData = await logsResponse.json();
    // Utilizando un bucle for...in
    for (const logKey in logsData) {
      if (logsData.hasOwnProperty(logKey)) {
        const logObject = logsData[logKey];
        // Populate with Solicitudes' Div
        const htmlLog = `<p class="${server}-log-text"> <br>[${logObject.time}] ${logObject.type} ${logObject.server} ${logObject.message}</p>`;
        const logTime = getSeconds(logObject.time);
        const logSet = {
          htmlLog: htmlLog,
          logTime: logTime
        }
        logs.push(logSet);
      }
    }
  }
}

/**
 * 
 * @param {string} time in format hh:mm:ss
 * @returns the timestamp recieved, but in seconds
 */
function getSeconds(time) {
  const timeArr = time.split(":");
  let seconds = 0;
  seconds += timeArr[0] * 3600;
  seconds += timeArr[1] * 60;
  seconds += timeArr[2];
  return seconds;
}
