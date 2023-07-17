const https = require('https')

/**
 * Get a list of all, recursive file info in that repository.
 */
const tree = ({user, repo, branch}) => {
  const host = 'api.github.com'
  const path = `/repos/${user}/${repo}/git/trees/${branch}?recursive=1`
  const method = 'GET'

  const options = {
    host,
    path,
    method,
    headers: {
      'user-agent': 'node-ghc'
    }
  }

  return new Promise((resolve, reject) => {
    const body = []
    https.get(options, res => {
      res
        .on('data', d => body.push(d))
        .on('end', () => {
          resolve(JSON.parse(Buffer.concat(body).toString()))
        })
    })
  })
}

console.log(tree("canftin", "myfileload", "master"))