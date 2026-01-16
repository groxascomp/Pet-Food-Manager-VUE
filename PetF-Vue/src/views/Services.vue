<template>
  <div
    class="min-h-screen"
    style="
      background: linear-gradient(-90deg, rgba(81, 104, 124, 0.0), rgba(56, 73, 111, 0.0)),
                 url('/cat-food-bg.jpg') center/cover no-repeat fixed;
      padding-top: 0px;
      padding-bottom: 0px;
    "
  >
    <section
      class="max-w-4xl mx-auto px-4 pt-4 pb-12 text-center font-sans"
      style="padding-top: 0px;"
    >
      <h1 class="text-6xl font-extrabold text-gray-800 mb-6">Tracking Food</h1>
      <h2 class="text-xl font-semibold text-gray-700 mb-8">🍽️ Food Served History 🍽️</h2><br />

      
      <div class="grid grid-cols-3 gap-6 max-w-3xl mx-auto mb-8">
        <div class="bg-white border border-blue-200 rounded-lg shadow p-6 flex flex-col items-center">
          <span class="text-gray-700 font-semibold text-lg mb-2">Average Meal per Day</span>
          <span class="text-blue-600 font-bold text-3xl">{{ mealsToday }}</span>
        </div>
        <div class="bg-white border border-green-200 rounded-lg shadow p-6 flex flex-col items-center">
          <span class="text-gray-700 font-semibold text-lg mb-2">Meals This Week</span>
          <span class="text-green-600 font-bold text-3xl">{{ mealsThisWeek }}</span>
        </div>
        <div class="bg-white border border-red-200 rounded-lg shadow p-6 flex flex-col items-center">
          <span class="text-gray-700 font-semibold text-lg mb-2">Unscheduled Meals</span>
          <span class="text-red-600 font-bold text-3xl">{{ unscheduledMeals }}</span>
        </div>
      </div>

     
      <div
        v-if="notificationMessage"
        class="bg-yellow-100 border border-yellow-400 text-yellow-800 px-4 py-3 rounded relative mb-12 max-w-2xl mx-auto"
      >
        <strong class="font-bold">Notice: </strong>
        <span class="block sm:inline">{{ notificationMessage }}</span>
      </div>

      
      <p v-if="logs.length === 0" class="text-gray-500 font-medium">No food served yet.</p>
      <div v-else class="overflow-x-auto w-full max-w-2xl mx-auto mt-8">
        <table class="min-w-full divide-y divide-gray-200 border border-gray-300 rounded-lg shadow-sm text-center font-sans bg-white">
          <thead class="bg-gray-100">
            <tr>
              <th class="px-6 py-3 text-xs font-medium text-gray-500 uppercase tracking-wider text-center">
                Event
              </th>
              <th class="px-6 py-3 text-xs font-medium text-gray-500 uppercase tracking-wider text-center">
                Date & Time
              </th>
            </tr>
          </thead>
          <tbody class="bg-white divide-y divide-gray-200">
            <tr
              v-for="(log, index) in logs"
              :key="log.id"
              :class="index === 0 ? 'bg-blue-50' : ''"
            >
              <td class="px-6 py-4 whitespace-nowrap text-sm text-gray-900 font-medium text-center">
                <div class="flex items-center justify-center">
                  <component :is="getIcon(log.event)" class="h-5 w-5 mr-2" />
                  <span>{{ log.event }}</span>
                </div>
              </td>
              <td class="px-6 py-4 whitespace-nowrap text-sm text-gray-700 font-medium text-center">
                {{ log.timestamp }}
              </td>
            </tr>
          </tbody>
        </table>
      </div>
    </section>
  </div>
</template>

<script setup>
import { ref, onMounted, onUnmounted, computed } from 'vue'
import { CheckCircleIcon, UserIcon } from '@heroicons/vue/24/solid'

const logs = ref([])

function parseTimestamp(ts) {
  const [datePart, timePart] = ts.split(' ')
  const [monthStr, day, year] = datePart.split('-')
  const [hour, minute] = timePart.split(':')

  const months = {
    Jan: 0, Feb: 1, Mar: 2, Apr: 3, May: 4, Jun: 5,
    Jul: 6, Aug: 7, Sep: 8, Oct: 9, Nov: 10, Dec: 11
  }

  return new Date(
    parseInt(year),
    months[monthStr],
    parseInt(day),
    parseInt(hour),
    parseInt(minute)
  )
}

async function fetchLogs() {
  try {
    const res = await fetch('https://petfeeder-8cf87-default-rtdb.asia-southeast1.firebasedatabase.app/logs.json')
    const data = await res.json()
    if (data) {
      const entries = Object.keys(data).map(key => ({
        id: key,
        ...data[key]
      }))
      entries.sort((a, b) => parseTimestamp(b.timestamp) - parseTimestamp(a.timestamp))
      logs.value = entries
    } else {
      logs.value = []
    }
  } catch (err) {
    console.error('Error fetching logs:', err)
  }
}

onMounted(() => {
  fetchLogs()
  const interval = setInterval(fetchLogs, 5000)
  onUnmounted(() => clearInterval(interval))
})

function getIcon(event) {
  const lower = event.toLowerCase()
  if (lower.includes('manual')) {
    return UserIcon
  }
  if (lower.includes('scheduled')) {
    return CheckCircleIcon
  }
  return null
}

// Tracker calculations
const mealsToday = computed(() => {
  const today = new Date().toDateString()
  return logs.value.filter(
    log => new Date(parseTimestamp(log.timestamp)).toDateString() === today
  ).length
})

const mealsThisWeek = computed(() => {
  const startOfWeek = new Date()
  startOfWeek.setDate(startOfWeek.getDate() - startOfWeek.getDay())
  return logs.value.filter(
    log => parseTimestamp(log.timestamp) >= startOfWeek
  ).length
})

const unscheduledMeals = computed(() =>
  logs.value.filter(log => log.event.toLowerCase().includes('manual')).length
)

// Notification message logic
const notificationMessage = computed(() => {
  if (mealsToday.value === 3) {
    return 'I would like to inform you that your pet’s daily food intake has exceeded the average recommended meal portion. It may be beneficial to monitor their diet closely to ensure balanced nutrition and overall well-being.'
  }
  if (mealsToday.value === 4) {
    return 'Providing your dog with meals that exceed the recommended portions may lead to a series of health problems. It is advisable to maintain a balanced feeding schedule to safeguard your pet’s overall well-being.'
  }
  if (mealsToday.value >= 5) {
    return 'Bro Stop, your dog is Chunk Dog now'
  }
  return null
})
</script>

<style scoped>

</style>
